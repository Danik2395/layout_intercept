#pragma once
#include <stdint.h>
#include <linux/input.h>
#include "types.h"

void implement_tap_hold(global_state_t* gs, internal_event_t* ev);
