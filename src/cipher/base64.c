#include "base64.h"

void base64_encode( const uint8_t *data, size_t len, uint8_t *ciphertext )
{
	size_t data_index = 0;
	size_t ciphertext_index = 0;

	while ( data_index < len )
	{
		ciphertext[ciphertext_index++] = BASE64[( ( data[data_index] & 0xFC ) >> 2 )];

		if ( ( data_index + 1 ) == len )
		{
			ciphertext[ciphertext_index++] = BASE64[( ( data[data_index] & 0x3 ) << 4 )];
			ciphertext[ciphertext_index++] = '=';
			ciphertext[ciphertext_index++] = '=';
			break;
		}

		ciphertext[ciphertext_index++] = BASE64[( ( ( data[data_index] & 0x3 ) << 4 ) |
														( ( data[data_index + 1] & 0xF0 ) >> 4 ) )];

		if ( ( data_index + 2 ) == len )
		{
			ciphertext[ciphertext_index++] = BASE64[( ( data[data_index + 1] & 0xF ) << 2 )];
			ciphertext[ciphertext_index++] = '=';
			break;
		}

		ciphertext[ciphertext_index++] = BASE64[( ( ( data[data_index + 1] & 0xF ) << 2 ) |
														( ( data[data_index + 2] & 0xC0 ) >> 6 ) )];
		ciphertext[ciphertext_index++] = BASE64[( data[data_index + 2] & 0x3F )];
		data_index += 3;
	}

	ciphertext[ciphertext_index] = '\0';
}

int	base64_decode( const uint8_t *ciphertext, size_t len, uint8_t *plaintext )
{
	size_t plaintext_index = 0;
	size_t ciphertext_index = 0;
	uint8_t first, second, third, fourth;
	uint8_t i;

	if( ( len & 0x03 ) )
	{
		fprintf( stderr, "Invalid ciphertext length\n" );
		return ( 1 );
	}

	while ( ciphertext_index < len )
	{
		for ( i = 0; i < 4; ++i )
		{
			if ( ( ciphertext[ciphertext_index + i] > 131 ) || ( UNBASE64[ciphertext[ciphertext_index + i]] == -1 ) )
			{
				fprintf(stderr, "Invalid base64 char, cannot decode: %c\n", ciphertext[ciphertext_index + i] );
				return ( 2 );
			}
		}

		first = UNBASE64[ciphertext[ciphertext_index]];
		second = UNBASE64[ciphertext[ciphertext_index + 1]];
		third = UNBASE64[ciphertext[ciphertext_index + 2]];
		fourth = UNBASE64[ciphertext[ciphertext_index + 3]];

		plaintext[plaintext_index++] = ( first << 2 ) | ( ( second & 0x30 ) >> 4 );

		if ( ciphertext[ciphertext_index + 2] != '=' )
			plaintext[plaintext_index++] = ( ( second & 0xF ) << 4 ) | ( ( third & 0x3C ) >> 2 );

		if ( ciphertext[ciphertext_index + 3] != '=' )
			plaintext[plaintext_index++] = ( ( third & 0x3 ) << 6 ) | fourth;

		ciphertext_index += 4;
	}

	plaintext[plaintext_index] = '\0';

	return ( 0 );
}
