#include "tap-hold.h"
#include "types.h"
#include "utils.h"
#include "poll_operations.h"
#include "debug.h"

static inline void swap_events(internal_event_t* ev, internal_event_t* ev1)
{
    internal_event_t temp_ev = *ev;
    *ev = *ev1;
    *ev1 = temp_ev;
}

int implement_tap_hold(global_state_t* gs, internal_event_t* ev)
{
    uint64_t diff_t = diff_time(gs->prev_key_time_ms, ev->key_time_ms);
    th_pending_t* thp = gs->th_pending;

    debug_val("tap-hold prev_time", "%lu", gs->prev_key_time_ms);
    debug_val("tap-hold  key_time", "%lu", ev->key_time_ms);
    debug_val("tap-hold  iff_time", "%lu", diff_t);

    if (ev->key_type == TAPHOLD)
    {
        if (thp[0].active)
        {
            if (ev->keystroke == DOWN)
            {
                ev->st_keycodes = gs->th_conf[ev->keycode_raw].hold_keycodes;
                if (diff_t < gs->th_conf[thp[0].event.keycode_raw].idle_time)
                {
                    debug("thbr 1");

                    timer_stop(gs->key_fds[thp[0].event.keycode_raw]);
                    timer_start(gs, ev, gs->th_conf[ev->keycode_raw].hold_time);
                    swap_events(ev, &thp[0].event);
                    ev->st_keycodes = gs->th_conf[ev->keycode_raw].tap_keycodes;
                }
                else
                {
                    debug("thbr 2");

                    thp[1].active = true;
                    thp[1].event = *ev;
                    timer_start(gs, ev, gs->th_conf[ev->keycode_raw].hold_time);
                    return 0;
                }
            }
            else
            {
                timer_stop(gs->key_fds[ev->keycode_raw]);
                ev->st_keycodes = gs->th_conf[ev->keycode_raw].tap_keycodes;

                if (ev->keycode_raw != thp[0].event.keycode_raw)
                {
                    if (thp[1].active)
                    {
                        debug("thbr 3");
                        debug_val("in triple resolv th to hold. thp[0].keycode", "%d", thp[0].event.keycodes[0]);

                        timer_stop(gs->key_fds[thp[0].event.keycode_raw]);
                        thp[0].active = false;
                        thp[1].active = false;

                        event_to_q(gs, &thp[0].event);

                        ev->keystroke = DOWN;
                        event_to_q(gs, ev);

                        ev->keystroke = UP;
                        event_to_q(gs, ev);
                    }
                }
                else
                {
                    thp[0].active = false;
                    if (gs->th_pending[1].active)
                    {
                        debug("thbr 4");

                        timer_stop(gs->key_fds[thp[1].event.keycode_raw]);
                        thp[1].active = false;

                        ev->keystroke = DOWN;
                        event_to_q(gs, ev);

                        thp[1].event.st_keycodes = gs->th_conf[thp[1].event.keycode_raw].tap_keycodes;
                        event_to_q(gs, &thp[1].event);
                    }
                    else
                    {
                        debug("thbr 5");

                        ev->keystroke = DOWN;
                        event_to_q(gs, ev);
                    }
                    ev->keystroke = UP;
                    event_to_q(gs, ev);
                }
            }
        }
        else
        {
            if (ev->keystroke == DOWN)
            {
                if (diff_t < gs->th_conf[ev->keycode_raw].idle_time)
                {
                    debug("thbr 6");
                    ev->st_keycodes = gs->th_conf[ev->keycode_raw].tap_keycodes;
                }
                else
                {
                    debug("thbr 7");

                    ev->st_keycodes = gs->th_conf[ev->keycode_raw].hold_keycodes;
                    thp[0].active = true;
                    thp[0].event = *ev;
                    timer_start(gs, ev, gs->th_conf[ev->keycode_raw].hold_time);
                    return 0;
                }
            }
        }

        return 1;
    }

    if (ev->keystroke == UP) return 1;

    timer_stop(gs->key_fds[thp[0].event.keycode_raw]);
    thp[0].active = false;

    if (diff_t < gs->th_conf[thp[0].event.keycode_raw].idle_time)
    {
        debug("thbr 8");
        thp[0].event.st_keycodes = gs->th_conf[thp[0].event.keycode_raw].tap_keycodes;
    }
    else
    {
        debug("thbr 9");
        thp[0].event.st_keycodes = gs->th_conf[thp[0].event.keycode_raw].hold_keycodes;
    }

    event_to_q(gs, &thp[0].event);
    event_to_q(gs, ev);

    return 1;
}
