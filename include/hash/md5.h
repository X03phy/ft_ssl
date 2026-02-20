#pragma once


/*
 * Includes
 */

#include <stdint.h> // uintX_t
#include <stddef.h> // size_t

/*
 * Structures
 */

typedef struct s_md5_ctx {
	uint32_t state[4];
	uint64_t bitlen;
	uint8_t buffer[64];
	size_t buffer_len;
} t_md5_ctx;


/*
 * Prototypes
 */

void md5(const uint8_t *data, const size_t len, uint8_t hash[16]);

int md5_init(t_md5_ctx *ctx);
int md5_update(t_md5_ctx *ctx, const uint8_t *data, const size_t len);
int md5_final(uint8_t hash[16], t_md5_ctx *ctx);

int md5_init_wrap(void *ctx);
int md5_update_wrap(void *ctx, const uint8_t *data, const size_t len);
int md5_final_wrap(uint8_t *out, void *ctx);
