#include <stdio.h>
#include <linux/input.h>
#include "finite_automaton.h"
#include "types.h"
#include "utils.h"

void finite_event(global_state_t* gs, const internal_event_t* ev)
{
    uint64_t time = get_time_ms();
    gs->prev_key_time_ms = time;

    pressed_state_t* key_state = &gs->pressed_state[ev->keycode];

    bool key_active = ev->keystroke ? true : false;
    key_state->active = key_active;

    if (ev->key_type > LAST_TO_SEND_KEY_TYPE)
    {
	if (!key_active) return;

	// if (ev->key_type == LAYER)
	// {
	key_state->key_send = 0;
	key_state->layer_held = ev->layer;
	key_state->time_send = time;
	// }

	// ...

	return;
    }

    if (key_active)
    {
	key_state->key_send = ev->keycode;
	key_state->layer_held = 0;
	key_state->time_send = time;
    }

    struct input_event raw_event = {
	.code = ev->keycode,
	.type = EV_KEY,
	.value = ev->keystroke,
	.time = {0, 0}
    };

    (void)fwrite(&raw_event, sizeof(raw_event), 1, stdout);
}
