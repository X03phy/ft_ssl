#include "md5.h"

static void md5_init( t_md5_ctx *ctx )
{
	ctx->state[0] = 0x67452301;
	ctx->state[1] = 0xefcdab89;
	ctx->state[2] = 0x98badcfe;
	ctx->state[3] = 0x10325476;

	ctx->bitlen = 0;
	ctx->buffer_len = 0;
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

static void md5_update( t_md5_ctx *ctx, const uint8_t *data, const size_t len )
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
}

static void md5_final( uint8_t hash[16], t_md5_ctx *ctx )
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
}

void md5( const uint8_t *data, size_t len, uint8_t hash[16] )
{
	t_md5_ctx ctx;

	md5_init( &ctx );
	md5_update( &ctx, data, len );
	md5_final( hash, &ctx );
}
