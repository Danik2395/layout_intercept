#include <stdbool.h>
#include <stdint.h>
#include <linux/input.h>
#include <linux/input-event-codes.h>
#include <time.h>
#include "utils.h"
#include "config.h"
#include "types.h"

uint64_t get_time_ms(void)
{
    struct timespec time;

    (void)clock_gettime(CLOCK_MONOTONIC, &time);

    return (uint64_t)time.tv_sec * 1000 + (uint64_t)time.tv_nsec / 1000000;
}

internal_event_t event_to_internal(const struct input_event* ev)
{
    internal_event_t internal_ev = {
        .keycode_raw = ev->code,
        .st_keycodes = {{ev->code}},
        .keystroke = ev->value,
        .key_time_ms = get_time_ms()
    };
    return internal_ev;
}

void make_key_type_lookup(global_state_t* gs)
{
    key_type_t* lookup = gs->key_type_lookup;

    for (int code = 0; code < KEY_CNT; ++code)
    {
        if      (taphold_config[code].configured) lookup[code] = TAPHOLD;
        else if (timer_config[code].configured)   lookup[code] = OVERLOAD_TIMER;
        // ...
    }

}

int postclassify_key_type(const global_state_t* gs, internal_event_t* ev)
{
    if (ev->key_type == NORMAL || ev->keycodes[0] <= KEY_MAX) return 0;

    if (ev->keycodes[0] & LAYER_BASE)
    {
        ev->key_type = LAYER;
        ev->layer = ev->keycodes[0] - LAYER_BASE;
    }

    // ...

    return 1;
}
