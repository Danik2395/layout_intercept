#pragma once
#include <linux/input.h>
#include <stdbool.h>
#include <stdint.h>
#include "types.h"

uint64_t timeval_to_ms(const struct timeval* tv);

internal_event_t event_to_internal(const struct input_event* ev);

bool wanted_key_mask(const struct input_event* ev);

void make_key_type_lookup(global_state_t* gs);

void preclassify_key_type(const global_state_t* gs, internal_event_t* ev);

// return 1 if type was classificated,
// return 0 if wasn't
int postclassify_key_type(const global_state_t* gs, internal_event_t* ev);
