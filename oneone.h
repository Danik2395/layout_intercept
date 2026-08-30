#pragma once
#include "types.h"

// return 1 if key was remapped,
// return 0 if wasn't
static inline int remap_key_oneone(const global_state_t* gs, internal_event_t* ev)
{
    key_batch_t oneone_keycodes = gs->oneone_conf[ev->keycode_raw];
    if (!oneone_keycodes.keycodes[0]) return 0;
    ev->st_keycodes = oneone_keycodes;
    return 1;
}
