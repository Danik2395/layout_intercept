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
#include "oneone.h"
#include "debug.h"

int main(void)
{
    // No bufferisation
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    struct input_event raw_event;
    internal_event_t event;

    global_state_t gs = {0};
    gs.th_conf = taphold_config;
    gs.timer_conf = timer_config;
    gs.layers_conf = layers_config;
    gs.oneone_conf = oneone_config;
    gs.q_pos = -1;

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
        int num_fds = epoll_wait(gs.epollfd, epoll_events, EPOLL_EVENTS_MAX, -1);
        debug("1. after epoll");

        if (num_fds == -1)
        {
            ret = 1;
            goto freefd;
        }

        for (int fd_idx = 0; fd_idx < num_fds; ++fd_idx)
        {
            struct epoll_event* epoll_event = &epoll_events[fd_idx];

            if (epoll_event->data.ptr == (void*)&stdin_marker)
            {
                if (!(epoll_event->events & EPOLLIN)) continue;

                if (read(STDIN_FILENO, &raw_event, sizeof(raw_event)) != sizeof(raw_event)) goto freefd;

                if (!wanted_event_mask(&raw_event))
                {
                    if (gs.suspend_event && raw_event.type == EV_SYN)
                    {
                        debug("suspend_event");
                        gs.suspend_event = false;
                        continue;
                    }

                    (void)write(STDOUT_FILENO, &raw_event, sizeof(raw_event));
                    continue;
                }
                gs.suspend_event = true;

                event = event_to_internal(&raw_event);
                preclassify_key_type(&gs, &event);

                debug("2. after event_to_internal");
                debug_val("keycode", "%d", event.keycodes[0]);
                debug_val("value  ", "%d", event.keystroke);
                debug_val("type   ", "%d", event.key_type);

                if (remap_key_layer(&gs, &event) || remap_key_oneone(&gs, &event))
                {
                    finite_event(&gs, &event);
                    continue;
                }

                debug_val("3. key_type before implement", "%d", event.key_type);

                if (event.key_type == TAPHOLD || (event.key_type == NORMAL && gs.th_pending.active))
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
                debug_val("on timer interupt. keycode", "%d", event.keycodes[0]);

                int on_timer_fd = gs.key_fds[event.keycode_raw];

                uint64_t buff_clean = 0;
                (void)read(on_timer_fd, &buff_clean, sizeof(uint64_t));

                if (event.key_type == TAPHOLD)
                {
                    gs.th_pending.active = false;
                }
            }

            int ev_idx = 0;
            do
            {
                internal_event_t* send_event = gs.q_pos == -1 ? &event : &gs.send_q[ev_idx];
                debug_val("4. q_pos", "%d", gs.q_pos);

                (void)postclassify_key_type(send_event);

                (void)handle_layer_key(&gs, send_event);

                if (send_event->key_type == LAYER)
                {
                    debug("main send layer");
                    finite_event(&gs, send_event);
                    continue;
                }
                // ...

                if (send_event->keystroke == UP)
                {
                    debug("main send up");
                    send_event->st_keycodes = gs.pressed_state[send_event->keycode_raw].keycodes_sent;
                    finite_event(&gs, send_event);
                    continue;
                }

                if (!is_remapped(send_event))
                {
                    debug_val("5. not remapped key", "%d", send_event->keycodes[0]);
                    (void)remap_key_layout(&gs, send_event);
                }

                finite_event(&gs, send_event);
            }
            while (gs.q_pos != -1 && ++ev_idx <= gs.q_pos);
            gs.q_pos = -1;
        }
    }

freefd:
    debug("freefd");
    close_fds(&gs);
    return ret;
}
