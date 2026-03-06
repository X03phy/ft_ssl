#pragma once

typedef struct s_rc4_ctx {
	uint8_t x, y;
	uint8_t S[256];
} t_rc4_ctx;

int rc4_init(t_rc4_ctx *ctx, const uint8_t *key, size_t len)
