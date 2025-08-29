#include "md5.h"

/* For SHA256() */
#include <openssl/md5.h>

/* For printf() */
#include <stdio.h>

/* For memcmp() */
#include <string.h>

int main( int argc, char **argv )
{
	if ( argc != 2 )
	{
		printf( "Please, enter only 1 argument\n" );
		return ( 1 );
	}

	unsigned char hash[16];
	unsigned char my_hash[16];

	MD5( ( const unsigned char * ) argv[1], strlen( argv[1] ), hash );
	printf( "openssl MD5: " );
	for ( uint8_t i = 0; i < 16; ++i )
		printf( "%02x", hash[i] );
	printf( "\n" );

	md5( ( const unsigned char * ) argv[1], strlen(argv[1]), my_hash );
	printf( "my MD5:      " );
	for ( uint8_t i = 0; i < 16; ++i )
		printf( "%02x", my_hash[i] );
	printf("\n");

	if ( !memcmp( ( const char * ) hash, ( const char * ) my_hash, 16 ) )
		printf( "OK\n" );
	else
		printf( "KO\n" );

	return ( 0 );
}
