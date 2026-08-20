#include <stdint.h>
#include "layers.h"
#include "types.h"

static layer_t keycode_to_layer_type(const internal_event_t* ev)
{
    return ev->keycode - LAYER_BASE;
}

int remap_key_layer(global_state_t* gs, internal_event_t* ev)
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

void handle_layer_key()
{

}
