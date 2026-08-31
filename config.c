#include <linux/input-event-codes.h>
#include <stdbool.h>
#include "config.h"
#include "types.h"

const th_conf_t taphold_config[KEY_CNT] = {
    [KEY_A] = {
        .idle_time     = 100,
        .hold_time     = 200,
        .tap_keycodes  = {{KEY_A}},
        .hold_keycodes = {{KEY_LEFTSHIFT}},
        .configured    = true,
    },
    [KEY_S] = {
        .idle_time     = 100,
        .hold_time     = 200,
        .tap_keycodes  = {{KEY_S}},
        .hold_keycodes = {{KEY_LEFTCTRL}},
        .configured    = true,
    },
    [KEY_L] = {
        .idle_time     = 100,
        .hold_time     = 200,
        .tap_keycodes  = {{KEY_L}},
        .hold_keycodes = {{KEY_RIGHTCTRL}},
        .configured    = true,
    },
    [KEY_SEMICOLON] = {
        .idle_time     = 100,
        .hold_time     = 200,
        .tap_keycodes  = {{KEY_SEMICOLON}},
        .hold_keycodes = {{KEY_RIGHTSHIFT}},
        .configured    = true,
    }
};

const timer_conf_t timer_config[KEY_CNT] = {
    [KEY_TAB] = {
        .hold_time     = 200,
        .tap_keycodes  = {{KEY_TAB}},
        .hold_keycodes = {{KEY_ESC}},
        .configured    = true,
    }
};

const key_batch_t layers_config[LAYERS_MAX_SIZE][KEY_CNT] = {
    [LAYER_ALT_MASK] = {
        [KEY_RIGHTALT]  = {{KEY_LEFTCTRL, KEY_BACKSPACE}},
        [KEY_BACKSPACE] = {{KEY_LEFTCTRL, KEY_BACKSPACE}}
    },
    [LAYER_NAV_MASK] = {
        [KEY_H] = {{KEY_LEFT}},
        [KEY_J] = {{KEY_DOWN}},
        [KEY_K] = {{KEY_UP}},
        [KEY_L] = {{KEY_RIGHT}}
    },
};

const key_batch_t oneone_config[KEY_CNT] = {
    [KEY_RIGHTALT] = {{KEY_BACKSPACE}}
};
