#include <unistd.h>
#include <linux/input.h>
#include "finite_automaton.h"
#include "types.h"
#include "utils.h"

void finite_event(global_state_t* gs, const internal_event_t* ev)
{
    uint64_t time = get_time_ms();
    gs->prev_key_time_ms = time;

    pressed_state_t* key_state = &gs->pressed_state[ev->keycode_raw];

    bool key_active = ev->keystroke ? true : false;
    key_state->active = key_active;

    if (ev->key_type > LAST_TO_SEND_KEY_TYPE)
    {
        if (!key_active) return;

        // if (ev->key_type == LAYER)
        // {
        key_state->keycodes_sent = (key_batch_t){0};
        key_state->layer_held = ev->layer;
        key_state->time_sent = time;
        // }

        // ...

        return;
    }

    if (key_active)
    {
        key_state->keycodes_sent = ev->st_keycodes;
        key_state->layer_held = 0;
        key_state->time_sent = time;
    }

    struct input_event flush_q[FLUSH_QUEUE_SIZE] = {0};

    int flush_ev_cnt = 0;
    int kc_idx = 0;
    while (kc_idx < BATCH_SIZE)
    {
        uint16_t keycode = ev->keycodes[kc_idx++];

        if (keycode == 0) break;

        struct input_event raw_event = {
            .type = EV_KEY,
            .code = keycode,
            .value = ev->keystroke,
            .time = {0, 0}
        };

        struct input_event report_event = {
            .type = EV_SYN,
            .code = SYN_REPORT,
            .value = 0,
            .time = {0, 0}
        };

        flush_q[flush_ev_cnt++] = raw_event;
        flush_q[flush_ev_cnt++] = report_event;
    }

    (void)write(STDOUT_FILENO, flush_q, sizeof(struct input_event) * (uint64_t)flush_ev_cnt);
}
