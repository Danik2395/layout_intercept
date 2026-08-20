#include <stdio.h>
#include <linux/input.h>
#include "finit_automaton.h"

void forward_event(const struct input_event* ev)
{
    fwrite(ev, sizeof(*ev), 1, stdout);
}

void send_event()
{

}
