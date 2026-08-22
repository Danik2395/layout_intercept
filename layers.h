#pragma once
#include <stdbool.h>
#include "types.h"

inline void layer_enable(layer_t* mask, layer_t layer)
{
    *mask |= layer;
    // 0000 0001
    // 0000 0010
    // 0000 0011
}

inline void layer_disable(layer_t* mask, layer_t layer)
{
    *mask &= ~layer;
    // 0000 0011
    // 1111 1110
    // 0000 0010
}

inline bool is_layer(const layer_t* mask, layer_t layer)
{
    return (*mask & layer) != 0;
}

static layer_t keycode_to_layer_type(const internal_event_t* ev);

// return 1 if key was remapped,
// return 0 if wasn't
int remap_key_layer(const global_state_t* gs, internal_event_t* ev);

// return 1 if layer was changed,
// return 0 if wasn't
int handle_layer_key(global_state_t* gs, const internal_event_t* ev);
