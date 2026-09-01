#pragma once
#include <linux/input-event-codes.h>
#include <stdint.h>
#include <stdbool.h>

#define EPOLL_EVENTS_MAX 16

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

#define LAST_TO_SEND_KEY_TYPE OVERLOAD_TIMER

typedef enum
{
    UP,
    DOWN,
    REPEAT
} keystroke_t;

#define BATCH_SIZE 4
#define QUEUE_SIZE 16
#define FLUSH_QUEUE_SIZE BATCH_SIZE * 2

typedef uint16_t batch_t[BATCH_SIZE];

typedef struct
{
    batch_t keycodes;
} key_batch_t;

typedef struct
{
    uint16_t keycode_raw;
    union
    {
        key_batch_t st_keycodes;
        batch_t keycodes;
    };
    layer_t layer;
    keystroke_t keystroke;
    key_type_t key_type;
    uint64_t key_time_ms;
} internal_event_t;

typedef struct
{
    uint64_t idle_time;
    uint64_t hold_time;
    key_batch_t tap_keycodes;
    key_batch_t hold_keycodes;
    bool configured;
} th_conf_t;

typedef struct
{
    uint64_t hold_time;
    key_batch_t tap_keycodes;
    key_batch_t hold_keycodes;
    bool configured;
} timer_conf_t;

typedef struct
{
    bool active;
    key_batch_t keycodes_sent;
    uint64_t time_sent;
    layer_t layer_held;
    key_type_t key_type;
} pressed_state_t;

typedef struct
{
    bool active;
    internal_event_t event;
} th_pending_t;

#define THP_SIZE 2

typedef struct
{
    uint64_t prev_key_time_ms;
    bool suspend_event;

    int epollfd;
    int key_fds[KEY_CNT];

    internal_event_t key_waiting[KEY_CNT];
    pressed_state_t pressed_state[KEY_CNT];

    int q_pos;
    internal_event_t send_q[QUEUE_SIZE];

    th_pending_t th_pending[THP_SIZE];
    const th_conf_t* th_conf; // size KEY_CNT

    const timer_conf_t* timer_conf; // size KEY_CNT

    const key_batch_t* oneone_conf; // size KEY_CNT

    layer_t layers_mask;
    const key_batch_t (*layers_conf)[KEY_CNT]; // size LAYERS_MAX_SIZE KEY_CNT

    key_type_t key_type_lookup[KEY_CNT];
} global_state_t;
