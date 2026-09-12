# layout_intercept

C plugin for [interception-tools](#src0) that I wrote for myself because using all-in-one deamons isn't as fancy.

It remaps physical qwerty layout to desired, manages layers and key overload: tap-hold, on timer expiration, one to one remap.

The goal was to replace xkb + keyd combo to use layout all across the system.

**WIP: wrong architecture decision in tap-hold logic. Queue needed for pending instead of slots.**

<!-- [Main repo]() -->

Navigation:
- [Features](#features)
- [Pipeline](#pipeline)
- [About everything](#about-everything)
- [Test](#test)
- [Dev log](#dev-log)
- [Sources](#sources)
- [Documentation](docs/docs.md)

---

## Features

- Zero dynamic memory allocation
    - All memory is on stack or in static segments of address space
- Zero compiler warnings tolerance
    - Compiled with `-Wall -Wextra -pedantic -Wconversion -Wshadow -Werror` flags
    - Validated by ASan (Address) and UBSan (Undefined Behavior)
- Single thread event-driven architecture
    - `epoll` + `timerfd`  native Linux combo
        - 0 cpu-bound when idle
        - Blocking resolving loop. Thus all is sequentially correct
- Procedure C Data-oriented-Design
    - `global_state_t` as structure of arrays
    - Data size optimization (see [internal_event_t.union](docs/docs.md#internal_event_t))
- Flat code & guard clauses
    - Adherence to the early return pattern wherever was possible
- Minimal overhead on I/O
    - Macro keys (e.g. ctrl+key) and key + syn_ev are written all at once.\
      In one `write()` call from array they've been collected into
    - Not using `fwrite()` and `fread()` because of no bufferisation.\
      These functions implement buffers inside them that leads to unnecesary overhead
- Hardware O(1) bitmask layer routing
    - Leading layer is found by using `__builtin_clz` [instruction](#src5) of GCC
- Physical key keycode as identificator
    - State tracking to avoid sticky keys
    - O(1) lookup for all of config and waiting arrays
    - No uncertanty whether data in `keycodes` are already mutated or not

## Pipeline

```

               Start plugin
                 - Bfferisation to null
                 - Initialize data
                 - Make configs
                 - Make fds for epoll

               |
               v

Main while

               Define type

               |
               v

               (from stdin) -----------------------------------------*
                                                                     |
               |                                                     |
               v                                                     |
                                                                     |
               (wanted event)                     -> forward it      |
                                                     contiue loop    |
                                                                     |
               |                                                     |
               v                                                     |
                                                                     |
               Suspend syn_ev                                        |
                                                                     |
               |                                                     |
               v                                                     |
                                                                     |
               Predefine key desteny                                 |
                 - event_to_internal                                 |
                 - preclassify_key_type                              |
                                                                     |
               |                                                     |
               v                                                     |
                                                                     |
               First tier remap                                      |
                 - remap_key_layer                                   |
                 - remap_key_oneone                                  |
                                                                     |
               |                                                     |
               v                                                     |
                                                                     |
               (remap occured)                    -> finite event    |
                                                     continue loop   |
                                                                     |
               |                                                     |
               v                                                     |
                                                                     |
Central functions                  Timer interrupt <-----------------*
  - implement_tap_hold             |
  - implement_overload_timer       |
               |                   |
               |                   |
               *-------------------*
               |
               v

               (send event)                       -> continue

               |
               v

Send do while

               Mutate event if alternative logic is set
                 - postclassify_key_type

               |
               v

               Toggle layer if needed
                 - handle_layer_key

               |
               v

               (key is mutated to non send type)  -> finite event
                                                     continue loop

               |
               v

               (key is UP type)                   -> take even from waiting
                                                     Toggle layer if needed
                                                     - handle_layer_key
                                                     finite event
                                                     continue loop

               |
               v

               (key is remapped)                  -> remap to desired layout
                                                     - remap_key_layout

               |
               v

               finite event

               |
               v

               (one send event)                   -> continue loop


```

## About everything

## Test

## Dev log

## Sources

0. [Interception-Tools](https://gitlab.com/interception/linux/tools)<span id="src0"></span>
1. [Event cods docs](https://docs.kernel.org/input/event-codes.html)<span id="src1"></span>
2. [epoll docs](https://man7.org/linux/man-pages/man7/epoll.7.html)<span id="src2"></span>
3. [timerfd docs](https://man7.org/linux/man-pages/man2/timerfd_create.2.html)<span id="src3"></span>
4. [clock_gettime docs](https://man7.org/linux/man-pages/man3/clock_gettime.3.html)<span id="src4"></span>
5. [__builtin_clz docs](https://gcc.gnu.org/onlinedocs/gcc/Bit-Operation-Builtins.html#index-_005f_005fbuiltin_005fctz)<span id="src5"></span>
6. [input_event() docs](https://www.kernel.org/doc/html/v4.16/driver-api/input.html#c.input_event)<span id="src6"></span>
7. []()<span id="src7"></span>
8. []()<span id="src8"></span>
9. []()<span id="src9"></span>
10. []()<span id="src10"></span>
11. []()<span id="src11"></span>
12. []()<span id="src12"></span>
13. []()<span id="src13"></span>
