#ifndef WHIRLPOOL_H
#define WHIRLPOOL_H

/* For uintX_t */
#include <stdint.h>

/* For size_t */
#include <stddef.h>

/* For memset() */
#include "memory.h"

void whirlpool( const uint8_t *data, size_t len, uint8_t hash[64] );

#endif
