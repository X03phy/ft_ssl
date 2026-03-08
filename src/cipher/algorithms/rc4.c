//#include "cipher/rc4.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>


typedef struct s_rc4_ctx {
	uint8_t x, y;
	uint8_t S[256];
} t_rc4_ctx;


int rc4_init(t_rc4_ctx *ctx, const uint8_t *key, const size_t len)
{
	uint8_t *S;
	size_t i;
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


int rc4_crypt(uint8_t *out, t_rc4_ctx *ctx, const uint8_t *in, const size_t len)
{
	uint8_t *S;
	uint8_t x, y, tx, ty;
	size_t i;

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


int main(void)
{
	uint8_t cipher[50];
	uint8_t text[] = "Plaintext";
	uint8_t *key = (uint8_t *)"Key";
	t_rc4_ctx ctx;
	size_t i;

	rc4_init(&ctx, key, 3);

	rc4_crypt(cipher, &ctx, text, 9);

	printf("Cipher: ");
	for (i = 0; i < 9; i++)
		printf("%02x", cipher[i]);
	printf("\n");

	return (0);
}
