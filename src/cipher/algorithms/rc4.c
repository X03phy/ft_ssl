#include "cipher/rc4.h"


typedef struct s_rc4_ctx {
	uint8_t x, y;
	uint8_t S[256];
} t_rc4_ctx;


int rc4_init(t_rc4_ctx *ctx, const uint8_t *key, size_t len)
{
	uint8_t *S;
	uint8_t i, j, tmp;
	size_t k;

	S = ctx->S;
	ctx->x = 0;
	ctx->y = 0;

	for (i = 0; i < 256; i += 1)
		S[i] = i;

	for (i = j = k = 0; i < 256; i += 1) {
		tmp = S[i];
		j = (key[k] + tmp + j) & 0xff;
		if (++k == len)
			k = 0;
		S[i] = S[j];
		S[j] = tmp;
	}
}


int rc4_crypt(uint8_t *outdata, const uint8_t *indata, )
{

	return (1);
}

