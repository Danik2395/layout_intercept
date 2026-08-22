#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <stdio.h>
#include <poll.h>
#include <stdbool.h>
#include <sys/poll.h>
#include "config.h"
#include "tap-hold.h"
#include "overload_timer.h"
#include "types.h"
#include "utils.h"
#include "finite_automaton.h"
#include "layout.h"
#include "layers.h"

int main(void)
{
    // No bufferisation
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    struct pollfd fds = {
	.fd = stdin,
	.events = POLLIN
    };

    struct input_event raw_event;
    internal_event_t event;

    global_state_t gs = {0};
    gs.th_conf = taphold_config;
    gs.layers_conf = layers_config;

    make_key_type_lookup(&gs);

    while (1)
    {
	int pr = poll(&fds, 1, );

	if (fds.revents & (POLLIN | POLLHUP))
	{
	    if (fread(&raw_event, sizeof(raw_event), 1, stdin) != 1) break;
	}

	if (pr > 0)
	{
	    if (!wanted_key_mask(&raw_event))
	    {
		if (gs.suspend_event)
		{
		    gs.suspend_event = false;
		    continue;
		}

		(void)fwrite(&raw_event, sizeof(raw_event), 1, stdout);
		continue;
	    }
	    gs.suspend_event = true;

	    event = event_to_internal(&raw_event);
	    preclassify_key_type(&gs, &event);

	    if (event.key_type == TAPHOLD || event.key_type == NORMAL && gs.th_pending.active)
	    {
		implement_tap_hold(&gs, &event);
	    }
	    else if (event.key_type == OVERLOAD_TIMER)
	    {
		implement_overload_timer(&gs, &event);
	    }

	    if (event.key_type != NORMAL && postclassify_key_type(&gs, &event))
	    {
		if (event.key_type == LAYER)
		{
		    handle_layer_key(&gs, &event);

		    finite_event(&gs, &event);

		    continue;
		}

		// ...
	    }

	    if (!remap_key_layer(&gs, &event))
	    {
		(void)remap_key_layout(&gs, &event);
	    }

	    finite_event(&gs, &event);
	}
	else if (pr == 0)
	{

	}
	else if (pr < 0) return 1;
    }

    return 0;
}
