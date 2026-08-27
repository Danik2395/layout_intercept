#include "tap-hold.h"
#include "types.h"
#include "utils.h"
#include "poll_operations.h"

static inline void swap_events(internal_event_t* ev, internal_event_t* ev1)
{
    internal_event_t temp_ev = *ev;
    *ev = *ev1;
    *ev1 = temp_ev;
}

int implement_tap_hold(global_state_t* gs, internal_event_t* ev)
{
    uint64_t diff_t = diff_time(gs->prev_key_time_ms, ev->key_time_ms);
    th_pending_t* thp = &gs->th_pending;

    if (ev->key_type == TAPHOLD)
    {
        if (thp->active)
        {
            if (ev->keystroke == DOWN)
            {
                timer_stop(gs->key_fds[thp->event.keycode_raw]);
                ev->st_keycodes = gs->th_conf[ev->keycode_raw].hold_keycodes;
                timer_start(gs, ev, gs->th_conf[ev->keycode_raw].hold_time);
                swap_events(ev, &thp->event);

                if (diff_t < gs->th_conf[thp->event.keycode_raw].idle_time)
                {
                    ev->st_keycodes = gs->th_conf[ev->keycode_raw].tap_keycodes;
                }
                else
                {
                    ev->st_keycodes = gs->th_conf[ev->keycode_raw].hold_keycodes;
                }

            }
            else
            {
                if (ev->keycode_raw == thp->event.keycode_raw)
                {
                    timer_stop(gs->key_fds[ev->keycode_raw]);
                    thp->active = false;
                    ev->st_keycodes = gs->th_conf[ev->keycode_raw].tap_keycodes;

                    ev->keystroke = DOWN;
                    event_to_q(gs, ev);

                    ev->keystroke = UP;
                    event_to_q(gs, ev);
                }
                else
                {
                    ev->st_keycodes = gs->pressed_state[ev->keycode_raw].keycodes_sent;
                }
            }
        }
        else
        {
            if (ev->keystroke == DOWN)
            {
                if (diff_t < gs->th_conf[ev->keycode_raw].idle_time)
                {
                    ev->st_keycodes = gs->th_conf[ev->keycode_raw].tap_keycodes;
                }
                else
                {
                    thp->active = true;
                    thp->event = *ev;
                    ev->st_keycodes = gs->th_conf[ev->keycode_raw].hold_keycodes;
                    timer_start(gs, ev, gs->th_conf[ev->keycode_raw].hold_time);
                    return 0;
                }
            }
            else
            {
                ev->st_keycodes = gs->pressed_state[ev->keycode_raw].keycodes_sent;
            }
        }

        return 1;
    }

        if (ev->keystroke == UP) return 1;

        timer_stop(gs->key_fds[thp->event.keycode_raw]);
        thp->active = false;

        if (diff_t < gs->th_conf[thp->event.keycode_raw].idle_time)
        {
            thp->event.st_keycodes = gs->th_conf[thp->event.keycode_raw].tap_keycodes;
        }
        else
        {
            thp->event.st_keycodes = gs->th_conf[thp->event.keycode_raw].hold_keycodes;
        }

        event_to_q(gs, &thp->event);
        event_to_q(gs, ev);

        return 1;
}
