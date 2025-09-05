#include "ft_ssl.h"

int main( int argc, char **argv )
{
	t_ssl_wfunc wfunc = NULL;
	t_ssl_cmd   cmd;
	
	ft_memset( &cmd, 0, sizeof(t_ssl_cmd) );

	if ( argc < 2 ) {
		ft_putstr_fd( "usage: ft_ssl command [flags] [file/string]\n", 2 );
		return ( 1 );
	}

	if ( argc == 2 && ft_strcmp( "help", argv[1] ) == 0 ) {
		print_help();
		return ( 0 );
	}

	cmd.name = argv[1];
	wfunc = parse_cmd( &cmd );
	if ( !wfunc )
		return ( 1 );

	return ( wfunc( argc, argv, &cmd ) );
}
