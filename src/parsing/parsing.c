#include "ft_ssl.h"

t_cmd_func get_cmd( char *cmd )
{
	for ( int i = 0; g_cmds[i].name; ++i ) {
		if ( ft_strcmp( g_cmds[i].name, cmd ) == 0 )
			return ( g_cmds[i].func );
	}
	print_invalid_command( cmd );
	return ( NULL );
}

int parse_input( int argc, char **argv, t_ssl_ctx *ssl_ctx )
{
	int    i = 2; // argv[1] = commande
	t_list *tmp;

	ft_memset( ssl_ctx, 0, sizeof(*ssl_ctx) );

	while ( i < argc )
	{
		if ( argv[i][0] == '-' )
		{
			if ( ft_strcmp( argv[i], "-p" ) == 0 )
				ssl_ctx->flags |= 1 << FLAG_P;
			else if ( ft_strcmp( argv[i], "-q" ) == 0 )
				ssl_ctx->flags |= 1 << FLAG_Q;
			else if ( ft_strcmp( argv[i], "-r" ) == 0 )
				ssl_ctx->flags |= 1 << FLAG_R;
			else if ( ft_strcmp( argv[i], "-s" ) == 0 )
			{
				if ( i + 1 >= argc )
				{
					ft_putstr_fd( "ft_ssl: option requires an argument -- s\n", 2 );
					return ( 0 );
				}
				// stocker la string associée à -s
				tmp = ft_lstnew( argv[++i] );
				if ( !tmp )
				{
					print_func_failed( "ft_lstnew()" );
					return ( 0 );
				}
				ft_lstadd_back( &ssl_ctx->strings, tmp );
			}
			else
			{
				print_invalid_flag( argv[i] );
				return ( 0 );
			}
		}
		else
		{
			// ici c’est un fichier
			tmp = ft_lstnew( argv[i] );
			if ( !tmp )
			{
				print_func_failed( "ft_lstnew()" );
				return ( 0 );
			}
			ft_lstadd_back( &ssl_ctx->files, tmp );
		}
		++i;
	}

	if ( ( ( 1 & ssl_ctx->flags ) != 0 ) || ( !ssl_ctx->strings && !ssl_ctx->files ) )
	{
		if ( !get_input_fd( 0, &(ssl_ctx->input), &(ssl_ctx->len) ) )
			return ( 0 );
	}

	return ( 1 );
}
