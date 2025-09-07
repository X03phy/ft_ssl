#include "ft_ssl.h"
#include "color_code.h"

/* For ft_putstr_fd(), ft_putchar_fd() */
#include "fd.h"

/* For ft_isprint() */
#include "char.h"


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

void print_invalid_command( const char *cmd )
{
	ft_putstr_fd( RED, 2 );
	ft_putstr_fd( "ft_ssl: Error: '", 2 );
	ft_putstr_fd( cmd, 2 );
	ft_putstr_fd( "' is an invalid command.\n", 2 );
	ft_putstr_fd( RST, 2 );
}

void print_invalid_flag( const char *flag )
{
	ft_putstr_fd( RED, 2 );
	ft_putstr_fd( "ft_ssl: Error: '", 2 );
	ft_putstr_fd( flag, 2 );
	ft_putstr_fd( "' is an invalid flag.\n", 2 );
	ft_putstr_fd( RST, 2 );
}

void print_invalid_file( const char *file )
{
	ft_putstr_fd( RED, 2 );
	ft_putstr_fd( "ft_ssl: Error: ", 2 );
	ft_putstr_fd( file, 2 );
	ft_putstr_fd( ": No such file or directory\n", 2 );
	ft_putstr_fd( RST, 2 );
}

void print_internal_error( const char *func )
{
	ft_putstr_fd( RED, 2 );
	ft_putstr_fd( "ft_ssl: internal error in ", 2 );
	ft_putstr_fd( func, 2 );
	ft_putchar_fd( '\n', 2 );
	ft_putstr_fd( RST, 2 );
}

void print_hash( uint8_t *hash, int len )
{
	static const char hex[17] = "0123456789abcdef";
	char buf[2];

	for ( int i = 0; i < len; ++i )
	{
		buf[0] = hex[hash[i] >> 4];   // nibble haut
		buf[1] = hex[hash[i] & 0xF];  // nibble bas
		ft_putchar_fd( buf[0], 1 );
		ft_putchar_fd( buf[1], 1 );
	}
}

void print_hash_input( const char *input, const char *name, int beginning, int quotes )
{
	static const char hex[17] = "0123456789abcdef";
	unsigned char c;
	char buf[5];
	int i = 0;

	if ( beginning )
	{
		if ( name )
			ft_putstr_fd( name, 1 );
		ft_putchar_fd( '(', 1 );
	}
	else
		ft_putchar_fd( ' ', 1 );
	if ( quotes )
		ft_putchar_fd( '\"', 1 );

	while ( input[i] )
	{
		c = ( unsigned char )input[i];
		if ( ft_isprint( input[i] ) )
			ft_putchar_fd( input[i], 1 );
		else
		{
			if ( input[i] == '\n' )
				ft_putstr_fd( BLU "\\n" RST, 1 );
			else
			{
				buf[0] = '\\';
				buf[1] = 'x';
				buf[2] = hex[c >> 4];
				buf[3] = hex[c & 0xF];
				buf[4] = '\0';
				ft_putstr_fd( BLU, 1 );
				ft_putstr_fd( buf, 1 );
				ft_putstr_fd( RST, 1 );
			}
		}
		++i;
	}

	if ( quotes )
		ft_putchar_fd( '\"', 1 );
	if ( beginning )
	{
		ft_putchar_fd( ')', 1 );
		ft_putstr_fd( "= ", 1 );
	}
}
