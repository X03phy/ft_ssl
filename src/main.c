#include "ft_ssl.h"

int main( int argc, char **argv )
{
	t_cmd_func wrapper;
	t_opts opts;

	if ( argc < 2 ) {
		ft_putstr_fd( "usage: ft_ssl command [flags] [file/string]\n", 2 );
		return ( 1 );
	}

	if ( argc == 2 && ft_strcmp( "help", argv[1] ) ) {
		print_help();
		return ( 0 );
	}

	wrapper = get_cmd( argv[1] );
	if ( !wrapper ) {
		print_help();
		return ( 1 );
	}

	if ( !parse_input( argc, argv, &opts ) ) {
		opts_clear( &opts );
		print_help();
		return ( 1 );
	}





	opts_clear( &opts );
	return (0);
}
