#include "ft_ssl.h"

void print_help( void )
{
	ft_putchar_fd( '\n', 1 );
	ft_putstr_fd( "Commands:\n", 1 );
	ft_putstr_fd( "md5\n", 1 );
	ft_putstr_fd( "sha256\n", 1 );
	ft_putstr_fd( "whirlpool\n", 1 );
	ft_putchar_fd( '\n', 1 );
	ft_putstr_fd( "Flags:\n", 1 );
	ft_putstr_fd( "-p -q -r -s\n", 1 );
}

void print_invalid_command( char *cmd )
{
	ft_putstr_fd( "ft_ssl: Error: '", 2 );
	ft_putstr_fd( cmd, 2 );
	ft_putstr_fd( "' is an invalid command.\n", 2 );
}

void print_invalid_flag( char *flag )
{
	ft_putstr_fd( "ft_ssl: Error: '", 2 );
	ft_putstr_fd( flag, 2 );
	ft_putstr_fd( "' is an invalid flag.\n", 2 );
}
