#include "ft_ssl.h"
#include "hash.h"

int parse_input( int argc, char **argv, t_ssl_hash_ctx *ctx )
{
	int    i = 2; // argv[1] = commande
	t_list *tmp;

	while ( i < argc )
	{
		if ( argv[i][0] == '-' )
		{
			if ( ft_strcmp( argv[i], "-p" ) == 0 )
				ctx->flags |= 1 << FLAG_P;
			else if ( ft_strcmp( argv[i], "-q" ) == 0 )
				ctx->flags |= 1 << FLAG_Q;
			else if ( ft_strcmp( argv[i], "-r" ) == 0 )
				ctx->flags |= 1 << FLAG_R;
			else if ( ft_strcmp( argv[i], "-s" ) == 0 )
			{
				if ( i + 1 >= argc )
				{
					ft_putstr_fd( "ft_ssl: option requires an argument -- s\n", 2 );
					print_help();
					return ( 0 );
				}
				// stocker la string associée à -s
				tmp = ft_lstnew( argv[++i] );
				if ( !tmp )
				{
					print_func_failed( "ft_lstnew()" );
					return ( 0 );
				}
				ft_lstadd_back( &ctx->strings, tmp );
			}
			else
			{
				print_invalid_flag( argv[i] );
				print_help();
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
			ft_lstadd_back( &ctx->files, tmp );
		}
		++i;
	}

	if ( ( ( ( FLAG_P + 1 ) & ctx->flags ) != 0 ) || ( !ctx->strings && !ctx->files ) )
	{
		if ( !get_input_fd( 0, &(ctx->input), &(ctx->len) ) )
			return ( 0 );
	}

	return ( 1 );
}