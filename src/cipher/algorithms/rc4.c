#include "cipher/rc4.h"

#include <stdint.h>  // uintX_t
#include <stddef.h>  // size_t


/*
 * Functions
 */

static int rc4_init(t_rc4_ctx *ctx, const uint8_t *key, const size_t len)
{
	uint8_t *S;
	size_t  i;
	uint8_t j, tmp;
	size_t  k;

	if (!ctx || !key || len == 0)
		return (0);

	S = ctx->S;
	ctx->x = 0;
	ctx->y = 0;

	for (i = 0; i < 256; i++)
		S[i] = i;

	for (i = j = k = 0; i < 256; i++) {
		tmp = S[i];
		j += tmp + key[k];
		if (++k == len)
			k = 0;
		S[i] = S[j];
		S[j] = tmp;
	}

	return (1);
}


static int rc4_crypt(t_rc4_ctx *ctx, uint8_t *out, const uint8_t *in, const size_t len)
{
	uint8_t *S;
	uint8_t x, y, tx, ty;
	size_t  i;

	if (!out || !ctx || !in)
		return (0);

	S = ctx->S;
	x = ctx->x;
	y = ctx->y;

	for (i = 0; i < len; i++) {
		x++;
		tx = S[x];
		y += tx;
		ty = S[y];
		S[x] = ty;
		S[y] = tx;
		out[i] = in[i] ^ S[(uint8_t)(tx + ty)];
	}

	ctx->x = x;
	ctx->y = y;

	return (1);
}


int rc4_init_wrap(void *ctx, const uint8_t *key, const size_t len)
{
	return (rc4_init((t_rc4_ctx *)ctx, key, len));
}


int rc4_crypt_wrap(void *ctx, uint8_t *out, const uint8_t *in, const size_t len)
{
	return (rc4_crypt((t_rc4_ctx *)ctx, out, in, len));
}
