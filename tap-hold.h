#pragma once
#include "types.h"

// return 1 to move key forward,
// return 0 when no key to send
int implement_tap_hold(global_state_t* gs, internal_event_t* ev);
