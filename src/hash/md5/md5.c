#include "md5.h"


/* Macros */
#define F(x, y, z) ((x & y) | (~x & z))
#define G(x, y, z) ((x & z) | (y & ~z))
#define H(x, y, z) (x ^ y ^ z)
#define I(x, y, z) (y ^ (x | ~z))
#define LEFTROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))


/* Global variables */
static const uint32_t R[64] = {
	7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};

static const uint32_t K[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};


/* Structures */


/* Code */
int md5_init( t_md5_ctx *ctx )
{
	ctx->state[0] = 0x67452301;
	ctx->state[1] = 0xefcdab89;
	ctx->state[2] = 0x98badcfe;
	ctx->state[3] = 0x10325476;

	ctx->bitlen = 0;
	ctx->buffer_len = 0;

	return (0);
}

static void md5_transform( t_md5_ctx *ctx )
{
	uint32_t W[16];
	uint32_t a, b, c, d;
	uint32_t f, g, tmp;
	uint8_t i;

	for ( i = 0; i < 16; ++i )
	{
		W[i] = ( ctx->buffer[i * 4] ) | ( ctx->buffer[i * 4 + 1] << 8 ) |
			   ( ctx->buffer[i * 4 + 2] << 16 ) | ( ctx->buffer[i * 4 + 3] << 24 );
	}

	a = ctx->state[0]; b = ctx->state[1]; c = ctx->state[2]; d = ctx->state[3];

	for ( i = 0; i < 64; ++i )
	{
		if ( i < 16 )
		{
			f = F( b, c, d );
			g = i;
		}
		else if ( i < 32 )
		{
			f = G( b, c, d );
			g = ( 5 * i + 1 ) % 16;
		}
		else if ( i < 48 )
		{
			f = H( b, c, d );
			g = ( 3 * i + 5 ) % 16;
		}
		else
		{
			f = I( b, c, d );
			g = ( 7 * i ) % 16;
		}

		tmp = d;
		d = c;
		c = b;
		b = b + LEFTROTATE( ( a + f + K[i] + W[g] ), R[i]);
		a = tmp;
	}

	ctx->state[0] += a;
	ctx->state[1] += b;
	ctx->state[2] += c;
	ctx->state[3] += d;
}

int md5_update( t_md5_ctx *ctx, const uint8_t *data, const size_t len )
{
	for ( size_t i = 0; i < len; ++i )
	{
		ctx->buffer[ctx->buffer_len++] = data[i];
		ctx->bitlen += 8;

		if ( ctx->buffer_len == 64 )
		{
			md5_transform( ctx );
			ctx->buffer_len = 0;
		}
	}

	return (1);
}

int md5_final( uint8_t hash[16], t_md5_ctx *ctx )
{
	ctx->buffer[ctx->buffer_len++] = 0x80;

	if ( ctx->buffer_len > 56 )
	{
		while ( ctx->buffer_len < 64 )
			ctx->buffer[ctx->buffer_len++] = 0x00;
		md5_transform( ctx );
		ctx->buffer_len = 0;
	}

	while ( ctx->buffer_len < 56 )
		ctx->buffer[ctx->buffer_len++] = 0x00;

	ctx->buffer[ctx->buffer_len++] = ctx->bitlen & 0xff;
	ctx->buffer[ctx->buffer_len++] = ( ctx->bitlen >> 8 ) & 0xff;
	ctx->buffer[ctx->buffer_len++] = ( ctx->bitlen >> 16 ) & 0xff;
	ctx->buffer[ctx->buffer_len++] = ( ctx->bitlen >> 24 ) & 0xff;
	ctx->buffer[ctx->buffer_len++] = ( ctx->bitlen >> 32 ) & 0xff;
	ctx->buffer[ctx->buffer_len++] = ( ctx->bitlen >> 40 ) & 0xff;
	ctx->buffer[ctx->buffer_len++] = ( ctx->bitlen >> 48 ) & 0xff;
	ctx->buffer[ctx->buffer_len++] = ( ctx->bitlen >> 56 ) & 0xff;

	md5_transform( ctx );

	for ( uint8_t i = 0; i < 4; ++i )
	{
		hash[i * 4] = ( ctx->state[i] ) & 0xff;
		hash[i * 4 + 1] = ( ctx->state[i] >> 8 ) & 0xff;
		hash[i * 4 + 2] = ( ctx->state[i] >> 16 ) & 0xff;
		hash[i * 4 + 3] = ( ctx->state[i] >> 24 ) & 0xff;
	}

	return (1);
}

void md5( const uint8_t *data, size_t len, uint8_t hash[16] )
{
	t_md5_ctx ctx;

	md5_init( &ctx );
	md5_update( &ctx, data, len );
	md5_final( hash, &ctx );
}

int md5_init_wrap(void *ctx)
{
	return md5_init((t_md5_ctx *)ctx);
}

int md5_update_wrap(void *ctx, const uint8_t *data, size_t len)
{
	return md5_update((t_md5_ctx *)ctx, data, len);
}

int md5_final_wrap(uint8_t *out, void *ctx)
{
	return md5_final(out, (t_md5_ctx *)ctx);
}
