#include "feistel.h"

static uint32_t feistel_function( uint32_t half, uint32_t subkey )
{
	return ( half ^ subkey );
}

int feistel_encrypt( const uint8_t *plaintext, size_t len, uint8_t *ciphertext, const uint8_t *key, int rounds )
{
	uint64_t block;
	uint32_t left;
	uint32_t right;
	uint32_t tmp;
	size_t i;
	int r;

	const uint64_t *longword_ptr =  ( uint64_t * ) plaintext;
	for ( i = 0; i < len; i += 8 )
	{
		block = *( uint64_t * )( plaintext + i );

		left = ( block >> 32 ) & 0xFFFFFFFF;
		right = block & 0xFFFFFFFF;

		for ( r = 0; r < rounds; r += 1 )
		{
			tmp = right;
			right = left ^ feistel_function( right, key[r] );
			left = tmp;
		}


		* ( uint64_t * ) &ciphertext = left | ( ( uint64_t ) right << 32 );
		ciphertext += 8;
	}

	return ( 0 );
}
