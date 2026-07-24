#pragma once
#include <linux/input.h>
#include <stdbool.h>

extern const __u16 qwerty2layout[KEY_MAX];
extern const __u16 qwerty2layout_shifted[KEY_MAX];

__u16 remap_key(__u16 keycode, bool is_shift);
