#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/epoll.h>
#include "config.h"
#include "tap-hold.h"
#include "overload_timer.h"
#include "types.h"
#include "utils.h"
#include "finite_automaton.h"
#include "layout.h"
#include "layers.h"
#include "poll_operations.h"

int main(void)
{
    // No bufferisation
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    struct input_event raw_event;
    internal_event_t event;

    global_state_t gs = {0};
    gs.th_conf = taphold_config;
    gs.layers_conf = layers_config;

    make_key_type_lookup(&gs);

    const char stdin_marker = 0;
    struct epoll_event epoll_events[EPOLL_EVENTS_MAX];
    struct epoll_event stdin_epoll_ev = {
        .events = EPOLLIN,
        .data.ptr = (void*)&stdin_marker
    };

    gs.epollfd = epoll_create(1);

    (void)epoll_ctl(gs.epollfd, EPOLL_CTL_ADD, STDIN_FILENO, &stdin_epoll_ev);

    make_key_fds(&gs);

    int ret = 0;
    while (1)
    {
        int nfds = epoll_wait(gs.epollfd, epoll_events, EPOLL_EVENTS_MAX, -1);

        if (nfds == -1)
        {
            ret = 1;
            goto freefd;
        }

        for (int n = 0; n < nfds; ++n)
        {
            struct epoll_event* epoll_event = &epoll_events[n];

            if (epoll_event->data.ptr == (void*)&stdin_marker)
            {
                if (!(epoll_event->events & EPOLLIN)) continue;

                if (fread(&raw_event, sizeof(raw_event), 1, stdin) != 1) goto freefd;

                if (!wanted_event_mask(&raw_event))
                {
                    if (gs.suspend_event && raw_event.type == EV_SYN)
                    {
                        gs.suspend_event = false;
                        continue;
                    }

                    (void)fwrite(&raw_event, sizeof(raw_event), 1, stdout);
                    continue;
                }
                gs.suspend_event = true;

                event = event_to_internal(&raw_event);
                preclassify_key_type(&gs, &event);

                if (remap_key_layer(&gs, &event))
                {
                    finite_event(&gs, &event);
                    continue;
                }

                if (event.key_type == TAPHOLD || event.key_type == NORMAL && gs.th_pending.active)
                {
                    if (!implement_tap_hold(&gs, &event)) continue;
                }
                else if (event.key_type == OVERLOAD_TIMER)
                {
                    if (!implement_overload_timer(&gs, &event)) continue;
                }
            }
            else // On timer interrupt
            {
                event = *(internal_event_t*)epoll_event->data.ptr; // From key_waiting

                int on_timer_fd = gs.key_fds[event.keycode_raw];

                int buff_clean = 0;
                (void)read(on_timer_fd, &buff_clean, sizeof(uint64_t));

                if (event.key_type == TAPHOLD)
                {
                    gs.th_pending.active = false;
                }
            }

            int n = 0;
            do
            {
                internal_event_t* send_event = gs.q_pos == -1 ? &event : &gs.send_q[n];

                if (send_event->key_type != NORMAL && postclassify_key_type(&gs, send_event))
                {
                    if (send_event->key_type == LAYER)
                    {
                        (void)handle_layer_key(&gs, send_event);

                        finite_event(&gs, send_event);

                        continue;
                    }

                    // ...
                }

                if (!send_event->remapped)
                {
                    (void)remap_key_layout(&gs, send_event);
                }

                finite_event(&gs, send_event);
            }
            while (gs.q_pos != -1 && ++n <= gs.q_pos);
            gs.q_pos = -1;
        }
    }

freefd:
    close_fds(&gs);
    return ret;
}
