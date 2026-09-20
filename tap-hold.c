#include "tap-hold.h"
#include "types.h"
#include "utils.h"
#include "poll_operations.h"
#include "debug.h"

void flush_thp_all(global_state_t* gs)
{
    th_pending_t* thp = gs->th_pending;

    int n = gs->thp_head;
    while (n != gs->thp_tail)
    {
        if (thp[n].event.key_type == TAPHOLD)
        {
            timer_stop(gs->key_fds[thp[n].event.keycode_raw]);

            const th_conf_t* thp_n_conf = &gs->th_conf[thp[n].event.keycode_raw];
            if (thp[n].active)
            {
                thp[n].event.st_keycodes = thp_n_conf->tap_keycodes;
            }
        }

        event_to_q(gs, &thp[n].event);

        n = (n + 1) % THP_SIZE;
    }

    gs->thp_head = gs->thp_tail = 0;
    thp[0].active = false;
}

int flush_thp_rebuild(global_state_t* gs)
{
    th_pending_t* thp = gs->th_pending;

    int n = gs->thp_head;
    while (n != gs->thp_tail)
    {
        if (thp[n].event.key_type == TAPHOLD)
        {
            if (thp[n].active)
            {
                gs->thp_head = n;
                return 1;
            }

            const th_conf_t* thp_n_conf = &gs->th_conf[thp[n].event.keycode_raw];
            thp[n].event.st_keycodes = thp_n_conf->tap_keycodes;
        }

        event_to_q(gs, &thp[n].event);

        n = (n + 1) % THP_SIZE;
    }

    gs->thp_head = gs->thp_tail = 0;
    thp[0].active = false;

    return 0;
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
        if (thp[gs->thp_head].active)
        {
            if (ev->keystroke == DOWN)
            {
                ev->st_keycodes = gs->th_conf[ev->keycode_raw].hold_keycodes;
                debug("thbr 2");

                event_to_thp(gs, ev);
                timer_start(gs, ev, gs->th_conf[ev->keycode_raw].hold_time);
                return 0;
            }
            else
            {
                event_to_thp(gs, ev);

                if (ev->keycode_raw == thp[gs->thp_head].event.keycode_raw)
                {
                    debug("thbr 3");
                    flush_thp_all(gs);
                }
                else
                {
                    debug("thbr 4");
                    thp[gs->thp_head].active = false;
                    flush_thp_all(gs);
                }
            }
        }
        else
        {
            if (ev->keystroke == DOWN)
            {
                if (diff_t < gs->th_conf[ev->keycode_raw].idle_time)
                {
                    debug("thbr 5");
                    ev->st_keycodes = gs->th_conf[ev->keycode_raw].tap_keycodes;
                }
                else
                {
                    debug("thbr 6");

                    ev->st_keycodes = gs->th_conf[ev->keycode_raw].hold_keycodes;
                    event_to_thp(gs, ev);
                    timer_start(gs, ev, gs->th_conf[ev->keycode_raw].hold_time);
                    return 0;
                }
            }
        }

        return 1;
    }

    event_to_thp(gs, ev);

    if (ev->keystroke == UP)
    {
        debug("thbr 7");
        thp[gs->thp_head].active = false;
        flush_thp_all(gs);
        return 1;
    }

    debug("thbr 8");

    return 0;
}
