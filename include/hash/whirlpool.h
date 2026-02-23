#pragma once


/*
 * Includes
 */

#include <stdint.h>  // uintX_t
#include <stddef.h>  // size_t


/*
 * Structures
 */

typedef struct s_whirlpool_ctx {
	uint64_t state[8];    // H0 to H7
	uint64_t bitlen;      // Total length in bits
	uint8_t  buffer[64];  // 512 bits (64 bytes) buffer
	size_t   buffer_len;  // Actual length of the buffer
} t_whirlpool_ctx;


/*
 * Prototypes
 */

int whirlpool(uint8_t hash[64], const uint8_t *data, const size_t len);

int whirlpool_init(t_whirlpool_ctx *ctx);
int whirlpool_update(t_whirlpool_ctx *ctx, const uint8_t *data, const size_t len);
int whirlpool_final(uint8_t digest[64], t_whirlpool_ctx *ctx);

int whirlpool_init_wrap(void *ctx);
int whirlpool_update_wrap(void *ctx, const uint8_t *data, const size_t len);
int whirlpool_final_wrap(uint8_t digest[64], void *ctx);
