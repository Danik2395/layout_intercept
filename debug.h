#pragma once
#include <stdio.h>

#ifdef DEBUG
#define debug(msg)                fprintf(stderr, "\033[32m %s \033[0m\n", msg)
#define debug_val(msg, form, val) fprintf(stderr, "\033[32m %s | " form "\033[0m\n", msg, val)
#else
#define debug(msg)
#define debug_val(msg, form, val)
#endif // DEBUG
