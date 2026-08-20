#pragma once
#include <linux/input.h>

void forward_event(const struct input_event* ev);

void send_event();
