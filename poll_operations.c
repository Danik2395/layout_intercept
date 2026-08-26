#include <linux/input-event-codes.h>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <unistd.h>
#include "types.h"
#include "utils.h"
#include "poll_operations.h"

void make_key_fds(global_state_t* gs)
{
    for (int code = 0; code < KEY_CNT; ++code)
    {
        if (!wanted_keycode(code)) continue;

        int timerfd = timerfd_create(CLOCK_MONOTONIC, 0);

        gs->key_fds[code] = timerfd;

        struct epoll_event epoll_ev = {
            .events = EPOLLIN,
        };

        (void)epoll_ctl(gs->epollfd, EPOLL_CTL_ADD, timerfd, &epoll_ev);
    }
}

void close_fds(global_state_t* gs)
{
    for (int code = 0; code < KEY_CNT; ++code)
    {
        if (!wanted_keycode(code)) continue;
        (void)close(gs->key_fds[code]);
    }
    (void)close(gs->epollfd);
}

static inline struct timespec ms_to_timespec(uint64_t ms)
{
    struct timespec ts = {
        .tv_sec = ms / 1000,
        .tv_nsec = (ms % 1000) * 1000000
    };
    return ts;
}

void timer_start(global_state_t* gs, const internal_event_t* ev, uint64_t ms)
{
    struct itimerspec timer = {
        .it_value = ms_to_timespec(ms)
    };

    (void)timerfd_settime(gs->key_fds[ev->keycode_raw], 0, &timer, NULL);

    internal_event_t* waiting_key = &gs->key_waiting[ev->keycode_raw];

    *waiting_key = *ev;

    struct epoll_event epoll_ev = {
        .events = EPOLLIN,
        .data.ptr = waiting_key
    };

    (void)epoll_ctl(gs->epollfd, EPOLL_CTL_MOD, gs->key_fds[ev->keycode_raw], &epoll_ev);
}

void timer_stop(int fd)
{
    struct itimerspec timer = {
        .it_value = {0, 0}
    };

    (void)timerfd_settime(fd, 0, &timer, NULL);
}
