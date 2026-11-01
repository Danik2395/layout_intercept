#pragma once
#include "types.h"

static inline void event_to_thp(global_state_t* gs, const internal_event_t* ev)
{
    gs->th_pending[gs->thp_tail].event = *ev;
    gs->th_pending[gs->thp_tail].active = true;
    gs->thp_tail = (gs->thp_tail + 1) % THP_SIZE;
}

void flush_thp_all(global_state_t* gs);

// return 1 if thp was rebuild,
// return 0 if wasn't
int flush_thp_rebuild(global_state_t* gs);

// return 1 to move key forward,
// return 0 when no key to send
int implement_tap_hold(global_state_t* gs, internal_event_t* ev);
