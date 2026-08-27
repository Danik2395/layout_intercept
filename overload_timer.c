#include "overload_timer.h"
#include "utils.h"
#include "poll_operations.h"

int implement_overload_timer(global_state_t* gs, internal_event_t* ev)
{
    if (ev->keystroke == DOWN)
    {
        ev->st_keycodes = gs->timer_conf[ev->keycode_raw].hold_keycodes;
        timer_start(gs, ev, gs->timer_conf[ev->keycode_raw].hold_time);
        return 0;
    }

    if (gs->pressed_state[ev->keycode_raw].active) return 1;

    timer_stop(gs->key_fds[ev->keycode_raw]);
    ev->st_keycodes = gs->timer_conf[ev->keycode_raw].tap_keycodes;

    ev->keystroke = DOWN;
    event_to_q(gs, ev);

    ev->keystroke = UP;
    event_to_q(gs, ev);

    return 1;
}
