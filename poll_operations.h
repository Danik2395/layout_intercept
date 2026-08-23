#pragma once
#include "types.h"

void make_key_fds(global_state_t* gs, int epollfd);

void close_key_fds(global_state_t* gs);

void timer_start(global_state_t* gs, const internal_event_t* ev);

void timer_stop(int fd);
