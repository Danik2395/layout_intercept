#include <stdbool.h>
#include <stdint.h>
#include <linux/input.h>
#include <linux/input-event-codes.h>
#include "pre-key.h"
#include "config.h"
#include "types.h"

uint64_t timeval_to_ms(const struct timeval* tv)
{
    return (uint64_t)tv->tv_sec * 1000 + (uint64_t)tv->tv_usec / 1000;
}

internal_event_t event_to_internal(const struct input_event* ev)
{
    internal_event_t internal_ev = {
	.keycode = ev->code,
	.keystroke = ev->value,
	.key_time_ms = timeval_to_ms(&ev->time)
    };
    return internal_ev;
}

bool wanted_key_mask(const struct input_event* ev)
{
    bool is_wanted_key = ev->type == EV_KEY &&                                         // Key
	ev->value < 2 &&                                                               // Not repeat
	(ev->code >= KEY_ESC && ev->code <= KEY_CAPSLOCK || ev->code == KEY_RIGHTALT); // Only valit keys
    return is_wanted_key;
}

void make_key_type_lookup(global_state_t* gs)
{
    key_type_t* lookup = gs->key_type_lookup;

    uint16_t key_num = 0;
    int key_index = KEY_MAX - 1;
    while (key_num != key_index)
    {
	if (taphold_config[key_num].configured)
	{
	    lookup[key_num] = TAPHOLD;
	}
    }

    key_num = 0;

    // ...
}

void preclassify_key_type(const global_state_t* gs, internal_event_t* ev)
{
    ev->key_type = gs->key_type_lookup[ev->keycode];
}

int postclassify_key_type(const global_state_t* gs, internal_event_t* ev)
{
    if (ev->keycode < KEY_MAX) return 0;

    if (ev->keycode & LAYER_BASE)
    {
	ev->key_type = LAYER;
    }

    // ...

    return 1;
}
