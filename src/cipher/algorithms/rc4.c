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
	uint8_t j, tmp;
	size_t  k;
	unsigned int i;

	S = ctx->S;
	ctx->x = 0;
	ctx->y = 0;

	for (i = 0; i < 256; i += 1)
		S[i] = i;

	for (i = j = k = 0; i < 256; i += 1) {
		tmp = S[i];
		j = (j + tmp + key[k]) & 0xff;

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

	S = ctx->S;
	x = ctx->x;
	y = ctx->y;

	i = 0;
	while (i < len)
	{
		x = (x + 1) & 0xFF;
		tx = S[x];
		y = (y + tx) & 0xFF;

		ty = S[y];
		S[x] = ty;
		S[y] = tx;

		out[i] = S[(tx + ty) & 0xFF] ^ in[i];
		i += 1;
	}

	ctx->x = x;
	ctx->y = y;

	return (1);
}


int main(void)
{
	uint8_t cipher[50];
	uint8_t text[] = "Hello";
	uint8_t *key = (uint8_t *)"World";
	t_rc4_ctx ctx;
	size_t i;

	rc4_init(&ctx, key, 5);

	rc4_crypt(cipher, &ctx, text, 5);

	printf("Cipher: ");
	for (i = 0; i < 5; i++)
		printf("%02x", cipher[i]);
	printf("\n");

	return (0);
}
