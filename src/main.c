#include "ft_ssl.h"

int main( int argc, char **argv )
{
	t_cmd_func wrapper;
	t_ssl_ctx ssl_ctx;

	if ( argc < 2 ) {
		ft_putstr_fd( "usage: ft_ssl command [flags] [file/string]\n", 2 );
		return ( 1 );
	}

	if ( argc == 2 && ft_strcmp( "help", argv[1] ) == 0 ) {
		print_help();
		return ( 0 );
	}

	wrapper = get_cmd( argv[1] );
	if ( !wrapper ) {
		print_help();
		return ( 1 );
	}

	if ( !parse_input( argc, argv, &ssl_ctx ) ) {
		ssl_ctx_clear( &ssl_ctx );
		print_help();
		return ( 1 );
	}

	wrapper(&ssl_ctx);



	ssl_ctx_clear( &ssl_ctx );
	return (0);
}
