#include "whirlpool.h"

/* For WHIRLPOOL */
#include <openssl/whrlpool.h>

/* For printf() */
#include <stdio.h>

int main( int argc, char **argv )
{
	if ( argc != 2 )
	{
		printf( "Please, enter only 1 argument\n" );
		return ( 1 );
	}

	unsigned char hash[64];
	unsigned char my_hash[64];

	WHIRLPOOL( ( const unsigned char * ) argv[1], strlen( argv[1] ), hash );
	printf( "openssl WHIRLPOOL: " );
	for ( uint8_t i = 0; i < 64; ++i )
		printf( "%02x", hash[i] );
	printf( "\n" );

	whirlpool( ( const unsigned char * ) argv[1], strlen( argv[1] ), my_hash );
	printf( "my WHIRLPOOL:      " );
	for ( uint8_t i = 0; i < 64; ++i )
		printf( "%02x", my_hash[i] );
	printf( "\n" );

	if ( !memcmp( ( const char * ) hash, ( const char * ) my_hash, 64 ) )
		printf( "OK\n" );
	else
		printf( "KO\n" );

	return ( 0 );
}
