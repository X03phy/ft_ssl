#include "base64.h"

static const char BASE64[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const int UNBASE64[132] = {
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 0-11
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 12-23
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 24-35
	-1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63, // 36-47
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -2, // 48-59
	-1,  0, -1, -1, -1,  0,  1,  2,  3,  4,  5,  6, // 60-71
	7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, // 72-83
	19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, // 84-95
	-1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, // 96-107
	37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, // 108-119
	49, 50, 51, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 120-131
};

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
