#pragma once
#include <linux/input-event-codes.h>
#include <stdint.h>
#include "types.h"

extern const th_conf_t taphold_config[KEY_CNT];

extern const key_batch_t layers_config[LAYERS_MAX_SIZE][KEY_CNT];
