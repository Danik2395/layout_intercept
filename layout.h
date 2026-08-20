#pragma once
#include <linux/input.h>
#include <stdbool.h>

extern const __u16 qwerty2layout[KEY_CNT];
extern const __u16 qwerty2layout_shifted[KEY_CNT];

__u16 remap_key_layout(__u16 keycode, bool is_shift);
