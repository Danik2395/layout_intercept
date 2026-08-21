#pragma once
#include <linux/input.h>
#include "types.h"

extern const uint16_t qwerty2layout[KEY_CNT];
extern const uint16_t qwerty2layout_shifted[KEY_CNT];

// return 1 if key was remapped,
// return 0 if wasn't
int remap_key_layout(const global_state_t* gs, internal_event_t* ev);
