#include "whirlpool.h"

static void whirlpool_init( t_whirlpool_ctx *ctx )
{
	memset( ctx->buffer, 0, sizeof( ctx->buffer ) );
	memset( ctx->state, 0, sizeof( ctx->state ) );

	ctx->bitlen = 0;
	ctx->buffer_len = 0;
}

static void whirlpool_transform( t_whirlpool_ctx *ctx )
{
	static const uint64_t RC[10] = {
		0x1823c6e887b8014f, 0x36a6d2f5796f9152, 0x60bc9b8ea30c7b35, 0x1de0d7c22e4bfe57, 0x157737e59ff04ada,
		0x58c9290ab1a06b85, 0xbd5d10f4cb3e0567, 0xe427418ba77d95d8, 0xfbee7c66dd17479e, 0xca2dbf07ad5a8333
	};

	uint64_t K[8], L[8], state[8], block[8];
	uint8_t i, r;

	for ( i = 0; i < 8; ++i )
	{
		block[i] =
			( ( uint64_t ) ctx->buffer[i * 8] << 56) |
			( ( uint64_t ) ctx->buffer[i * 8 + 1] << 48) |
			( ( uint64_t ) ctx->buffer[i * 8 + 2] << 40) |
			( ( uint64_t ) ctx->buffer[i * 8 + 3] << 32) |
			( ( uint64_t ) ctx->buffer[i * 8 + 4] << 24) |
			( ( uint64_t ) ctx->buffer[i * 8 + 5] << 16) |
			( ( uint64_t ) ctx->buffer[i * 8 + 6] << 8) |
			( ( uint64_t ) ctx->buffer[i * 8 + 7]);

		K[i] = ctx->state[i];
		state[i] = block[i] ^ ctx->state[i];
	}

	for ( r = 0; r < 10; ++r )
	{
		for ( i = 0; i < 8; ++i )
		{
			L[i] = C0[( K[i] >> 56 ) & 0xFF] ^
				   C1[( K[( i - 1 ) & 7] >> 48 ) & 0xFF] ^
				   C2[( K[( i - 2 ) & 7] >> 40 ) & 0xFF] ^
				   C3[( K[( i - 3 ) & 7] >> 32 ) & 0xFF] ^
				   C4[( K[( i - 4 ) & 7] >> 24 ) & 0xFF] ^
				   C5[( K[( i - 5 ) & 7] >> 16 ) & 0xFF] ^
				   C6[( K[( i - 6 ) & 7] >> 8 ) & 0xFF] ^
				   C7[( K[( i - 7 ) & 7] ) & 0xFF];
		}
		L[0] ^= RC[r];
		for ( i = 0; i < 8; ++i )
			K[i] = L[i];

		for ( i = 0; i < 8; ++i )
		{
			L[i] = C0[( state[i] >> 56 ) & 0xFF] ^
				   C1[( state[( i - 1 ) & 7] >> 48 ) & 0xFF] ^
				   C2[( state[( i - 2 ) & 7] >> 40 ) & 0xFF] ^
				   C3[( state[( i - 3 ) & 7] >> 32 ) & 0xFF] ^
				   C4[( state[( i - 4 ) & 7] >> 24 ) & 0xFF] ^
				   C5[( state[( i - 5 ) & 7] >> 16 ) & 0xFF] ^
				   C6[( state[( i - 6 ) & 7] >> 8 ) & 0xFF] ^
				   C7[( state[( i - 7 ) & 7] ) & 0xFF] ^
				   K[i];
		}
		for ( i = 0; i < 8; ++i )
			state[i] = L[i];
	}

	for ( i = 0; i < 8; ++i )
		ctx->state[i] ^= state[i] ^ block[i];
}

static void whirlpool_update( t_whirlpool_ctx *ctx, const uint8_t *data, const size_t len )
{
	for ( size_t i = 0; i < len; ++i )
	{
		ctx->buffer[ctx->buffer_len++] = data[i];
		ctx->bitlen += 8;

		if ( ctx->buffer_len == 64 )
		{
			whirlpool_transform( ctx );
			ctx->buffer_len = 0;
		}
	}
}

static void whirlpool_final( uint8_t hash[64], t_whirlpool_ctx *ctx )
{
	ctx->buffer[ctx->buffer_len++] = 0x80;

	if ( ctx->buffer_len > 32 )
	{
		while ( ctx->buffer_len < 64 )
			ctx->buffer[ctx->buffer_len++] = 0x00;
		whirlpool_transform( ctx );
		ctx->buffer_len = 0;
	}

	while ( ctx->buffer_len < 56 )
		ctx->buffer[ctx->buffer_len++] = 0x00;

	ctx->buffer[ctx->buffer_len++] = ( ctx->bitlen >> 56 ) & 0xff;
	ctx->buffer[ctx->buffer_len++] = ( ctx->bitlen >> 48 ) & 0xff;
	ctx->buffer[ctx->buffer_len++] = ( ctx->bitlen >> 40 ) & 0xff;
	ctx->buffer[ctx->buffer_len++] = ( ctx->bitlen >> 32 ) & 0xff;
	ctx->buffer[ctx->buffer_len++] = ( ctx->bitlen >> 24 ) & 0xff;
	ctx->buffer[ctx->buffer_len++] = ( ctx->bitlen >> 16 ) & 0xff;
	ctx->buffer[ctx->buffer_len++] = ( ctx->bitlen >> 8 ) & 0xff;
	ctx->buffer[ctx->buffer_len++] = ctx->bitlen & 0xff;

	whirlpool_transform( ctx );

	for ( uint8_t i = 0; i < 8; ++i )
	{
		hash[i * 8] = ( ctx->state[i] >> 56 ) & 0xff;
		hash[i * 8 + 1] = ( ctx->state[i] >> 48 ) & 0xff;
		hash[i * 8 + 2] = ( ctx->state[i] >> 40 ) & 0xff;
		hash[i * 8 + 3] = ( ctx->state[i] >> 32 ) & 0xff;
		hash[i * 8 + 4] = ( ctx->state[i] >> 24 ) & 0xff;
		hash[i * 8 + 5] = ( ctx->state[i] >> 16 ) & 0xff;
		hash[i * 8 + 6] = ( ctx->state[i] >> 8 ) & 0xff;
		hash[i * 8 + 7] = ctx->state[i] & 0xff;
	}
}

void whirlpool( const uint8_t *data, size_t len, uint8_t hash[64] )
{
	t_whirlpool_ctx ctx;

	whirlpool_init( &ctx );
	whirlpool_update( &ctx, data, len );
	whirlpool_final( hash, &ctx );
}
