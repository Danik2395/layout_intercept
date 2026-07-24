#include <stdio.h>
#include "helpers.h"

bool wanted_key_mask(struct input_event* ev)
{
    bool is_wanted_key = ev->type == EV_KEY &&                                         // Key
	ev->value < 2 &&                                                               // Not repeat
	(ev->code >= KEY_ESC && ev->code <= KEY_CAPSLOCK || ev->code == KEY_RIGHTALT); // Only valit keys
    return is_wanted_key;
}

void send_event(const struct input_event* ev)
{
    fwrite(ev, sizeof(*ev), 1, stdout);
}
