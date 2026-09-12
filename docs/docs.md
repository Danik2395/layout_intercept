# Documentation

Navigation:
- [types](#types)
    - [EPOLL_EVENTS_MAX](#epoll_events_max)
    - [LAYER_SHIFT_MASK](#layer_shift_mask)
    - [LAYER_CTRL_MASK](#layer_ctrl_mask)
    - [LAYER_ALT_MASK](#layer_alt_mask)
    - [LAYER_NAV_MASK](#layer_nav_mask)
    - [LAYERS_MAX_SIZE](#layers_max_size)
    - [LAYER_BASE](#layer_base)
    - [LAST_TO_SEND_KEY_TYPE](#last_to_send_key_type)
    - [BATCH_SIZE](#batch_size)
    - [QUEUE_SIZE](#queue_size)
    - [FLUSH_QUEUE_SIZE](#flush_queue_size)
    - [THP_SIZE](#thp_size)
    - [layer_t](#layer_t)
    - [key_type_t](#key_type_t)
    - [keystroke_t](#keystroke_t)
    - [batch_t](#batch_t)
    - [key_batch_t](#key_batch_t)
    - [internal_event_t](#internal_event_t)
    - [th_conf_t](#th_conf_t)
    - [timer_conf_t](#timer_conf_t)
    - [pressed_state_t](#pressed_state_t)
    - [th_pending_t](#th_pending_t)
    - [global_state_t](#global_state_t)
- [utils](#utils)
    - [wanted_keycode](#static-inline-bool-wanted_keycodeuint16_t-code)
    - [wanted_event_mask](#static-inline-bool-wanted_event_maskconst-struct-input_event-ev)
    - [preclassify_key_type](#static-inline-void-preclassify_key_typeconst-global_state_t-gs-internal_event_t-ev)
    - [event_to_q](#static-inline-void-event_to_qglobal_state_t-gs-const-internal_event_t-ev)
    - [diff_time](#static-inline-uint64_t-diff_timeuint64_t-t-uint64_t-t1)
    - [keycodes_equal_ptr](#static-inline-bool-keycodes_equal_ptrconst-key_batch_t-k-const-key_batch_t-k1)
    - [keycodes_equal_val](#static-inline-bool-keycodes_equal_valconst-key_batch_t-k-key_batch_t-k1)
    - [is_remapped](#static-inline-bool-is_remappedinternal_event_t-ev)
    - [get_time_ms](#uint64_t-get_time_msvoid)
    - [event_to_internal](#internal_event_t-event_to_internalconst-struct-input_event-ev)
    - [make_key_type_lookup](#void-make_key_type_lookupglobal_state_t-gs)
    - [postclassify_key_type](#int-postclassify_key_typeinternal_event_t-ev)
- [debug](#debug)
    - [debug](#debugmsg)
    - [debug_val](#debug_valmsg-form-val)
- [finite-automaton](#finite-automaton)
    - [finite_event](#void-finite_eventglobal_state_t-gs-const-internal_event_t-ev)
- [layout](#layout)
    - [qwerty2layout](#extern-const-key_batch_t-qwerty2layoutkey_cnt)
    - [qwerty2layout_shifted](#extern-const-key_batch_t-qwerty2layout_shiftedkey_cnt)
    - [remap_key_layout](#int-remap_key_layoutconst-global_state_t-gs-internal_event_t-ev)
- [layers](#layers)
    - [layers_config](#extern-const-key_batch_t-layers_configlayers_max_sizekey_cnt)
    - [layer_enable](#static-inline-void-layer_enablelayer_t-mask-layer_t-layer)
    - [layer_disable](#static-inline-void-layer_disablelayer_t-mask-layer_t-layer)
    - [is_layer](#static-inline-bool-is_layerlayer_t-mask-layer_t-layer)
    - [remap_key_layer](#int-remap_key_layerconst-global_state_t-gs-internal_event_t-ev)
    - [handle_layer_key](#int-handle_layer_keyglobal_state_t-gs-const-internal_event_t-ev)
- [oneone](#oneone)
    - [oneone_config](#extern-const-key_batch_t-oneone_configkey_cnt)
    - [remap_key_oneone](#static-inline-int-remap_key_oneoneconst-global_state_t-gs-internal_event_t-ev)
- [tap-hold](#tap-hold)
    - [taphold_config](#extern-const-th_conf_t-taphold_configkey_cnt)
    - [swap_events](#static-inline-void-swap_eventsinternal_event_t-ev-internal_event_t-ev1)
    - [implement_tap_hold](#int-implement_tap_holdglobal_state_t-gs-internal_event_t-ev)
- [overload-timer](#overload-timer)
    - [timer_config](#extern-const-timer_conf_t-timer_configkey_cnt)
    - [implement_overload_timer](#int-implement_overload_timerglobal_state_t-gs-internal_event_t-ev)
- [poll-operations](#poll-operations)
    - [ms_to_timespec](#static-inline-struct-timespec-ms_to_timespecuint64_t-ms)
    - [make_key_fds](#void-make_key_fdsglobal_state_t-gs)
    - [close_fds](#void-close_fdsglobal_state_t-gs)
    - [timer_start](#void-timer_startglobal_state_t-gs-const-internal_event_t-ev-uint64_t-ms)
    - [timer_stop](#void-timer_stopint-fd)
- [intercept](#intercept)
    - [main](#int-mainvoid)


## types

### EPOLL_EVENTS_MAX

### LAYER_SHIFT_MASK

### LAYER_CTRL_MASK

### LAYER_ALT_MASK

### LAYER_NAV_MASK

### LAYERS_MAX_SIZE

### LAYER_BASE

### LAST_TO_SEND_KEY_TYPE

### BATCH_SIZE

### QUEUE_SIZE

### FLUSH_QUEUE_SIZE

### THP_SIZE

### layer_t

- uint8_t

### key_type_t

- NORMAL
- TAPHOLD
- OVERLOAD_TIMER
- LAYER

### keystroke_t

- UP
- DOWN
- REPEAT

### batch_t

- uint16_t[BATCH_SIZE]

### key_batch_t

- keycodes

### internal_event_t

- keycode_raw
- union
    - st_keycodes
    - keycodes
- layer
- keystroke
- key_type
- key_time_ms

### th_conf_t

- idle_time
- hold_time
- tap_keycodes
- hold_keycodes
- configured

### timer_conf_t

- hold_time
- tap_keycodes
- hold_keycodes
- configured

### pressed_state_t

- active
- keycodes_sent
- time_sent
- layer_held
- key_type

### th_pending_t

- active
- event

### global_state_t

- prev_key_time_ms
- suspend_event
- epollfd
- key_fds[KEY_CNT]
- key_waiting[KEY_CNT]
- pressed_state[KEY_CNT]
- q_pos
- send_q[QUEUE_SIZE]
- th_pending[THP_SIZE]
- th_conf
- timer_conf
- oneone_conf
- layers_mask
- layers_conf
- key_type_lookup[KEY_CNT]

## utils

### static inline bool wanted_keycode(uint16_t code);

### static inline bool wanted_event_mask(const struct input_event* ev);

### static inline void preclassify_key_type(const global_state_t* gs, internal_event_t* ev);

### static inline void event_to_q(global_state_t* gs, const internal_event_t* ev);

### static inline uint64_t diff_time(uint64_t t, uint64_t t1);

### static inline bool keycodes_equal_ptr(const key_batch_t* k, const key_batch_t* k1);

### static inline bool keycodes_equal_val(const key_batch_t* k, key_batch_t k1);

### static inline bool is_remapped(internal_event_t* ev);

### uint64_t get_time_ms(void);

### internal_event_t event_to_internal(const struct input_event* ev);

### void make_key_type_lookup(global_state_t* gs);

### int postclassify_key_type(internal_event_t* ev);

## debug

### debug(msg)

### debug_val(msg, form, val)

## finite-automaton

### void finite_event(global_state_t* gs, const internal_event_t* ev);

## layout

### extern const key_batch_t qwerty2layout[KEY_CNT];

### extern const key_batch_t qwerty2layout_shifted[KEY_CNT];

### int remap_key_layout(const global_state_t* gs, internal_event_t* ev);

## layers

### extern const key_batch_t layers_config[LAYERS_MAX_SIZE][KEY_CNT];

### static inline void layer_enable(layer_t* mask, layer_t layer);

### static inline void layer_disable(layer_t* mask, layer_t layer);

### static inline bool is_layer(layer_t mask, layer_t layer);

### int remap_key_layer(const global_state_t* gs, internal_event_t* ev);

### int handle_layer_key(global_state_t* gs, const internal_event_t* ev);

## oneone

### extern const key_batch_t oneone_config[KEY_CNT];

### static inline int remap_key_oneone(const global_state_t* gs, internal_event_t* ev);

## tap-hold

### extern const th_conf_t taphold_config[KEY_CNT];

### static inline void swap_events(internal_event_t* ev, internal_event_t* ev1);

### int implement_tap_hold(global_state_t* gs, internal_event_t* ev);

## overload-timer

### extern const timer_conf_t timer_config[KEY_CNT];

### int implement_overload_timer(global_state_t* gs, internal_event_t* ev);

## poll-operations

### static inline struct timespec ms_to_timespec(uint64_t ms);

### void make_key_fds(global_state_t* gs);

### void close_fds(global_state_t* gs);

### void timer_start(global_state_t* gs, const internal_event_t* ev, uint64_t ms);

### void timer_stop(int fd);

## intercept

### int main(void);
