#include <stdint.h>
#include "layers.h"
#include "types.h"

int remap_key_layer(const global_state_t* gs, internal_event_t* ev)
{
    uint8_t mask = gs->layers_mask;
    uint16_t keycode = ev->keycode_raw;

    while (mask > 0)
    {
        layer_t highest_layer = 1U << (31 - __builtin_clz(mask));

        key_batch_t replacement_keycodes = gs->layers_conf[highest_layer][keycode];

        if (replacement_keycodes.keycodes[0])
        {
            ev->st_keycodes = replacement_keycodes;
            return 1;
        }

        mask &= ~highest_layer;
    }

    return 0;
}

int handle_layer_key(global_state_t* gs, const internal_event_t* ev)
{
    layer_t layer = ev->layer;
    bool layer_enabled = is_layer(gs->layers_mask, layer);

    int layer_changed = 0;

    if (ev->keystroke == DOWN && !layer_enabled)
    {
        layer_enable(&gs->layers_mask, layer);
        layer_changed = 1;
    }
    else if (ev->keystroke == UP && layer_enabled)
    {
        layer_disable(&gs->layers_mask, layer);
        layer_changed = 1;
    }

    return layer_changed;
}
