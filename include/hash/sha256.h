#pragma once


/*
 * Includes
 */

#include <stdint.h>  // uintX_t
#include <stddef.h>  // size_t


/*
 * Structures
 */

typedef struct s_sha256_ctx {
	uint32_t state[8];    // H0 to H7
	uint64_t bitlen;      // Total length in bits
	uint8_t  buffer[64];  // 512 bits (64 bytes) buffer
	size_t   buffer_len;  // Actual length of the buffer
} t_sha256_ctx;


/*
 * Prototypes
 */

void sha256(uint8_t digest[32], const uint8_t *data, const size_t len);

void sha256_init(t_sha256_ctx *ctx);
void sha256_update(t_sha256_ctx *ctx, const uint8_t *data, const size_t len);
void sha256_final(uint8_t digest[32], t_sha256_ctx *ctx);

void sha256_init_wrap(void *ctx);
void sha256_update_wrap(void *ctx, const uint8_t *data, const size_t len);
void sha256_final_wrap(uint8_t digest[32], void *ctx);
