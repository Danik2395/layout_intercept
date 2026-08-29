#include <stdint.h>
#include <linux/input-event-codes.h>
#include "layers.h"
#include "types.h"
#include "utils.h"

int remap_key_layer(const global_state_t* gs, internal_event_t* ev)
{
    uint8_t mask = gs->layers_mask;
    uint16_t keycode = ev->keycode_raw;

    while (mask > 0)
    {
        layer_t highest_layer = (layer_t)(1U << (31 - __builtin_clz(mask)));

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
    layer_t layer_to_toggle = 0;

    if (!layer)
    {
        key_batch_t keycodes_tail = ev->st_keycodes;
        keycodes_tail.keycodes[0] = 0;

        if (keycodes_equal_val(&keycodes_tail, (key_batch_t){0}))
        {
            switch (ev->keycodes[0])
            {
                case KEY_LEFTSHIFT:
                case KEY_RIGHTSHIFT:
                    layer_to_toggle = LAYER_SHIFT_MASK;
                    break;

                case KEY_LEFTCTRL:
                case KEY_RIGHTCTRL:
                    layer_to_toggle = LAYER_CTRL_MASK;
                    break;

                case KEY_LEFTALT:
                    layer_to_toggle = LAYER_ALT_MASK;
                    break;

                default:
                    break;
            }
        }
    }
    else
    {
        layer_to_toggle = layer;
    }

    if (layer_to_toggle == 0) return 0;

    if (ev->keystroke == DOWN)
    {
        layer_enable(&gs->layers_mask, layer_to_toggle);
    }
    else if (ev->keystroke == UP)
    {
        layer_disable(&gs->layers_mask, layer_to_toggle);
    }

    return 1;
}
