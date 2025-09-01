#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"
#include "fd.h"

static void print_invalid_command( char *cmd )
{
	ft_putstr_fd( "ft_ssl: Error: '", 2 );
	ft_putstr_fd( cmd, 2 );
	ft_putstr_fd( "' is an invalid command.\n", 2 );
}

static void print_invalid_flag( char *flag )
{
	ft_putstr_fd( "ft_ssl: Error: '", 2 );
	ft_putstr_fd( flag, 2 );
	ft_putstr_fd( "' is an invalid flag.\n", 2 );
}

typedef struct s_opts {
    int flag_p;
    int flag_q;
    int flag_r;
    int flag_s;
    char **strings; // tableau de chaînes après -s
    int  strings_count;
    char **files;   // tableau de fichiers
    int  files_count;
} t_opts;

int parse_input(int argc, char **argv, t_opts *opts)
{
    int i = 2; // argv[1] = commande

    ft_memset( opts, 0, sizeof(*opts) );

    while (i < argc) {
        if ( argv[i][0] == '-' ) {
            if ( ft_strcmp( argv[i], "-p" ) == 0 )
                opts->flag_p = 1;
            else if ( ft_strcmp( argv[i], "-q" ) == 0 )
                opts->flag_q = 1;
            else if ( ft_strcmp( argv[i], "-r" ) == 0 )
                opts->flag_r = 1;
            else if ( ft_strcmp( argv[i], "-s" ) == 0 ) {
                if ( i + 1 >= argc ) {
                    ft_putstr_fd( "ft_ssl: option requires an argument -- s\n", 2 );
                    return ( 0 );
                }
                // stocker la string associée à -s
                opts->strings[opts->strings_count++] = argv[++i];
            }
            else {
                print_invalid_flag( argv[i] );
                return (0);
            }
        }
        else {
            // ici c’est un fichier
            opts->files[opts->files_count++] = argv[i];
        }
        ++i;
    }
    return ( 1 );
}

// ft_ssl: Error: 'foobar' is an invalid command.

static void print_help( void )
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

int main( int argc, char **argv )
{
	t_opts opts;

	if ( argc < 2 ) {
		ft_putstr_fd( "usage: ft_ssl command [flags] [file/string]\n", 2 );
		return ( 1 );
	}

	if ( is_valid_command )

	if ( !parse_input( argc, argv, &opts ) ) {
		print_help();
		return ( 1 );
	}

	return (0);
}
