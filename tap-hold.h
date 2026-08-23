#pragma once
#include <stdint.h>
#include <linux/input.h>
#include "types.h"

// return 1 to send key forward,
// return 0 when timer set
int implement_tap_hold(global_state_t* gs, internal_event_t* ev);
