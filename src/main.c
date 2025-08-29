
#define FLAG_P 1
#define FLAG_Q 2
#define FLAG_R 4
#define FLAG_S 8

#include <stdio.h>

int main( int argc, char **argv )
{
	if ( argc < 2 ) {
		write( 2, "usage: ft_ssl command [flags] [files...]\n", 42 );
		return ( 1 );
	}


	return ( 0 );
}
