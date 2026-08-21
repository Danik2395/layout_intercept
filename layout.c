#include <stdint.h>
#include "layout.h"
#include "types.h"
#include "layers.h"

int remap_key_layout(const global_state_t* gs, internal_event_t* ev)
{
    uint16_t mapped = 0;

    if (is_layer(&gs->layers_mask, LAYER_SHIFT_MASK))
    {
	mapped = qwerty2layout_shifted[ev->keycode];

	if (mapped)
	{
	    ev->keycode = mapped;
	    return 1;
	}
    }

    mapped = qwerty2layout[ev->keycode];

    if (mapped)
    {
	ev->keycode = mapped;
	return 1;
    }

    return 0;
}
