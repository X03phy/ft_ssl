#include "ft_ssl.h"

/* For open() */
#include <fcntl.h>

/* For lists */
#include "linked_list.h"

/* For ft_putstr_fd(), ft_putchar_fd() */
#include "fd.h"

/* For ft_memset() */
#include "memory.h"

/* For ft_strcmp(), ft_strlen() */
#include "string.h"


/* Macros */
#define FLAG_P 0
#define FLAG_Q 1
#define FLAG_R 2


/* Structures */
typedef struct s_ssl_hash_ctx {
	int    flags;
	char   *input;
	size_t len;
	t_list *strings;
	t_list *files;
} t_ssl_hash_ctx;


/* Code */
static int parse_input( int argc, char **argv, t_ssl_hash_ctx *ctx )
{
	int    i = 2; // argv[1] = command
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
				// store the string after -s
				tmp = ft_lstnew( argv[++i] );
				if ( !tmp )
				{
					print_internal_error( "ft_lstnew()" );
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
			// here it's a file
			tmp = ft_lstnew( argv[i] );
			if ( !tmp )
			{
				print_internal_error( "ft_lstnew()" );
				return ( 0 );
			}
			ft_lstadd_back( &ctx->files, tmp );
		}
		++i;
	}

	if ( ( ( ( FLAG_P + 1 ) & ctx->flags ) != 0 ) || ( !ctx->strings && !ctx->files ) )
	{
		if ( !get_content_fd( 0, &(ctx->input), &(ctx->len) ) )
			return ( 0 );
	}

	return ( 1 );
}

static inline int flag_active( int n, int f )
{
	return ( ( n >> f ) & 1 );
}

static void hash_input( t_ssl_cmd *cmd, t_ssl_hash_ctx *ctx, uint8_t *hash )
{
	if ( flag_active( ctx->flags, FLAG_P ) || ( !ctx->files && !ctx->strings ) )
	{
		if ( !flag_active( ctx->flags, FLAG_Q ) )
		{
			if ( flag_active( ctx->flags, FLAG_P ) )
				print_hash_input( ctx->input, NULL, 1, 1 );
			else if ( !flag_active( ctx->flags, FLAG_R ) )
			{
				ft_putstr_fd( cmd->name, 1 );
				ft_putstr_fd( "(stdin)= ", 1 );
			}
		}

		cmd->hash.hash_func( ( const uint8_t * )ctx->input, ctx->len, hash );

		print_hash( hash, cmd->hash.hash_size );

		if ( !flag_active( ctx->flags, FLAG_Q ) && !flag_active( ctx->flags, FLAG_P ) && flag_active( ctx->flags, FLAG_R ) )
			ft_putstr_fd( " stdin", 1 );
		ft_putchar_fd( '\n', 1 );
	}
}

static void hash_strings( t_ssl_cmd *cmd, t_ssl_hash_ctx *ctx, uint8_t *hash )
{
	t_list *tmp = ctx->strings;

	while ( tmp )
	{
		if ( !flag_active( ctx->flags, FLAG_Q ) && !flag_active( ctx->flags, FLAG_R ) )
			print_hash_input( tmp->content, cmd->name, 1, 1 );

		cmd->hash.hash_func( ( const uint8_t * )tmp->content, ft_strlen( tmp->content ), hash );

		print_hash( hash, cmd->hash.hash_size );

		if ( !flag_active( ctx->flags, FLAG_Q ) && flag_active( ctx->flags, FLAG_R ) )
			print_hash_input( tmp->content, NULL, 0, 1 );
		ft_putchar_fd( '\n', 1 );

		tmp = tmp->next;
	}
}

static int hash_files( t_ssl_cmd *cmd, t_ssl_hash_ctx *ctx, uint8_t *hash )
{
	int    fd;
	char   *content;
	size_t len;
	t_list *tmp = ctx->files;

	while ( tmp )
	{
		fd = open( tmp->content, 0644, O_RDONLY );
		if ( fd == -1 )
		{
			print_invalid_file( tmp->content );
			tmp = tmp->next;
			continue;
		}
		if ( !get_content_fd( fd, &content, &len ) )
		{
			print_internal_error( "get_content_fd()" );
			close( fd );
			return ( 1 );
		}
		cmd->hash.hash_func( ( uint8_t * )content, len, hash );
		close( fd );
		free( content );

		if ( !flag_active( ctx->flags, FLAG_Q ) && !flag_active( ctx->flags, FLAG_R ) )
			print_hash_input( tmp->content, cmd->name, 1, 0 );

		print_hash( hash, cmd->hash.hash_size );

		if ( !flag_active( ctx->flags, FLAG_Q ) && flag_active( ctx->flags, FLAG_R ) )
			print_hash_input( tmp->content, NULL, 0, 0 );
		ft_putchar_fd( '\n', 1 );

		tmp = tmp->next;
	}

	return ( 0 );
}

static void free_ssl_hash_ctx( t_ssl_hash_ctx *ctx )
{
	ft_lstfree( &ctx->strings );
	ft_lstfree( &ctx->files );
	if ( ctx->input )
		free( ctx->input );
}

int hash_wrapper( int argc, char **argv, t_ssl_cmd *cmd )
{
	int exit_code;
	uint8_t hash[64];
	t_ssl_hash_ctx ctx;

	ft_memset( &ctx, 0, sizeof(ctx) );

	if ( !parse_input( argc, argv, &ctx ) )
		return ( 1 );

	hash_input( cmd, &ctx, hash );
	hash_strings( cmd, &ctx, hash );
	exit_code = hash_files( cmd, &ctx, hash );
	
	free_ssl_hash_ctx( &ctx );

	return ( exit_code );
}
