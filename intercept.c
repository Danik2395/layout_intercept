#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <stdio.h>
#include <poll.h>
#include <stdbool.h>
#include <sys/poll.h>
#include "config.h"
#include "types.h"
#include "utils.h"
#include "finite_automaton.h"
#include "layout.h"

int main(void)
{
    // No bufferisation
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    struct pollfd fds = {
	.fd = stdin,
	.events = POLLIN
    };

    struct input_event event;
    internal_event_t internal_event;

    global_state_t gs = {0};
    gs.th_conf = taphold_config;
    gs.layers_conf = layers_config;

    (void)make_key_type_lookup(&gs);

    while (1)
    {
	int pr = poll(&fds, 1, );

	if (fds.revents & (POLLIN | POLLHUP))
	{
	    if (fread(&event, sizeof(event), 1, stdin) != 1) break;
	}

	if (pr > 0)
	{
	    if (!wanted_key_mask(&event)) continue; // не континью тут. тут нужно, чтобы оно съедало ивенты синхронизации,
						    // которые идут после вонтед_ки
						    // а ещё нужно пропускать все остальные ивенты

	    internal_event = event_to_internal(&event);
	}
	else if (pr == 0)
	{

	}
	else if (pr < 0) return 1;
    }

    return 0;
}
