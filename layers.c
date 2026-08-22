#include <stdint.h>
#include "layers.h"
#include "types.h"

static layer_t keycode_to_layer_type(const internal_event_t* ev)
{
    return ev->keycode - LAYER_BASE;
}

int remap_key_layer(const global_state_t* gs, internal_event_t* ev)
{
    uint8_t mask = gs->layers_mask;
    uint16_t keycode = ev->keycode;

    while (mask > 0)
    {
	layer_t highest_layer = 1U << (31 - __builtin_clz(mask));

	uint16_t replasement_key = gs->layers_conf[highest_layer][keycode];

	if (replasement_key)
	{
	    ev->keycode = replasement_key;
	    return 1;
	}

	mask &= ~highest_layer;
    }

    return 0;
}

int handle_layer_key(global_state_t* gs, const internal_event_t* ev)
{
    layer_t layer = keycode_to_layer_type(ev);
    bool layer_enabled = is_layer(gs->layers_mask, layer);

    int layer_changed = 0;

    if (ev->keystroke == DOWN && layer_enabled)
    {
	layer_enable(&gs->layers_mask, layer);
	layer_changed = 1;
    }
    else if (ev->keystroke == UP && !layer_enabled)
    {
	layer_disable(&gs->layers_mask, layer);
	layer_changed = 1;
    }

    return layer_changed;
}
