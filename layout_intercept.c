#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <stdio.h>
#include <stdbool.h>
#include "helpers.h"
#include "layout.h"

static bool IS_SHIFT = false;

void toggle_shift(struct input_event* ev)
{
    if (!(ev->code == KEY_LEFTSHIFT || ev->code == KEY_RIGHTSHIFT)) return;
    IS_SHIFT = ev->value ? true : false;
}

void process_key(struct input_event* ev)
{
    toggle_shift(ev);
    ev->code = remap_key(ev->code, IS_SHIFT);
    send_event(ev);
}

int main(void)
{
    // No bufferisation
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    struct input_event event;

    // While only one full structure
    while (fread(&event, sizeof(event), 1, stdin) == 1) {
	if (!wanted_key_mask(&event))
	{
	    send_event(&event);
	    continue;
	}

	process_key(&event);
    }

    return 0;
}
