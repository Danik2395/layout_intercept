#pragma once
#include <linux/input-event-codes.h>
#include <stdint.h>
#include <stdbool.h>

#define LAYER_SHIFT_MASK (1U << 0)
#define LAYER_CTRL_MASK  (1U << 1)
#define LAYER_ALT_MASK   (1U << 2)
#define LAYER_NAV_MASK   (1U << 3)
#define LAYERS_MAX_SIZE  (1U << 3) + 1

#define LAYER_BASE (1U << 10)
// ...
// #define _BASE (1U << 15) // uint16_t for keycode

typedef uint8_t layer_t;

typedef enum
{
    NORMAL,         // Need to send normal keys to th func
    TAPHOLD,
    OVERLOAD_TIMER, // Only send overload keys for overload func
    LAYER           // Toggles layer
} key_type_t;

typedef enum
{
    DOWN,
    UP,
    REPEAT
} keystroke_t;

typedef struct
{
    uint16_t keycode;
    keystroke_t keystroke;
    key_type_t key_type;
    uint64_t key_time_ms;
} internal_event_t;

typedef struct
{
    uint64_t idle_time;
    uint64_t hold_time;
    uint16_t tap_key;
    uint16_t hold_key;
    bool configured;
} th_conf_t;

typedef struct
{
    bool active;
    uint16_t key_send;
    uint64_t time_send;
    layer_t layer_held;
} pressed_state_t;

typedef struct
{
    bool active;
    internal_event_t event;
} th_pending_t;

typedef struct
{
    uint64_t prev_key_time_ms;
    pressed_state_t pressed_state[KEY_CNT];

    const th_conf_t* th_conf; // size KEY_CNT

    layer_t layers_mask;
    const uint16_t (*layers_conf)[KEY_CNT]; // size LAYERS_MAX_SIZE KEY_CNT

    key_type_t key_type_lookup[KEY_CNT];
} global_state_t;
