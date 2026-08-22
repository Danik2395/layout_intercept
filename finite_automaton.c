#include <stdio.h>
#include <linux/input.h>
#include "finite_automaton.h"
#include "types.h"
#include "utils.h"

void finite_event(global_state_t* gs, const internal_event_t* ev)
{
    struct input_event raw_event = {
	.code = ev->keycode,
	.type = EV_KEY,
	.value = ev->keystroke,
	.time = {0, 0}
    };

    gs->prev_key_time_ms = get_time_ms();

    if (ev->key_type > LAST_TO_SEND_KEY_TYPE) return;

    (void)fwrite(&raw_event, sizeof(raw_event), 1, stdout);
}
