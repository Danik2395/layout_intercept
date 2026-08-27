#pragma once
#include <linux/input.h>
#include <stdbool.h>
#include <stdint.h>
#include "types.h"

static inline bool wanted_keycode(uint16_t code)
{
    return (code >= KEY_ESC && code <= KEY_CAPSLOCK || code == KEY_RIGHTALT);
}

static inline bool wanted_event_mask(const struct input_event* ev)
{
    bool is_wanted_key = ev->type == EV_KEY && // Key
        ev->value < 2 &&                       // Not repeat
        wanted_keycode(ev->code);              // Only valid keys
    return is_wanted_key;
}

static inline void preclassify_key_type(const global_state_t* gs, internal_event_t* ev)
{
    ev->key_type = gs->key_type_lookup[ev->keycode_raw];
}

static inline void event_to_q(global_state_t* gs, const internal_event_t* ev)
{
    gs->send_q[++gs->q_pos] = *ev;
}

static inline uint64_t diff_time(uint64_t t, uint64_t t1)
{
    uint64_t diff = t - t1;
    return diff > 0 ? diff : -diff;
}

static inline bool keycodes_equal(const key_batch_t* k, const key_batch_t* k1)
{
    return *(uint64_t*)k == *(uint64_t*)k1;
}

static inline void set_remapped(internal_event_t* ev)
{
    key_batch_t batch_raw = {ev->keycode_raw};
    if (!keycodes_equal(&batch_raw, &ev->st_keycodes)) ev->remapped = true;
}

uint64_t get_time_ms();

internal_event_t event_to_internal(const struct input_event* ev);

void make_key_type_lookup(global_state_t* gs);

void preclassify_key_type(const global_state_t* gs, internal_event_t* ev);

// return 1 if type was classificated (type changed),
// return 0 if wasn't
int postclassify_key_type(const global_state_t* gs, internal_event_t* ev);
