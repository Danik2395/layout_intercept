#pragma once
#include <linux/input.h>
#include <stdbool.h>

bool wanted_key_mask(struct input_event* ev);
void send_event(const struct input_event* ev);
