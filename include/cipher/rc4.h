#pragma once


/*
 * Includes
 */

#include <stdint.h>  // uintX_t
#include <stddef.h>  // size_t


/*
 * Structures
 */

typedef struct s_rc4_ctx {
	uint8_t x, y;
	uint8_t S[256];
} t_rc4_ctx;


/*
 * Prototypes
 */

/* cipher/algorithms/rc4.c */
int rc4_init(t_rc4_ctx *ctx, const uint8_t *key, const size_t len);
int rc4_crypt(uint8_t *out, t_rc4_ctx *ctx, const uint8_t *in, const size_t len);
