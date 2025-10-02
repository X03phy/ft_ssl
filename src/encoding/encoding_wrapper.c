#include "ft_ssl.h"

/* For open() */
#include <fcntl.h>

/* For lists */
#include "linked_list.h"

/* For ft_putstr_fd(), ft_putchar_fd() */
#include "fd.h"

/* For ft_memset() */
#include "memory.h"

/* For ft_strcmp(), ft_strlen(), ft_strremove() */
#include "string.h"


/* Macros */
#define FLAG_E 0
#define FLAG_D 1


/* Structures */
typedef struct s_ssl_encoding_ctx {
	int    flags;
	char   *input;
	size_t len;
	t_list *inf;
	t_list *outf;
} t_ssl_encoding_ctx;


/* Code */
static int parse_input( int argc, char **argv, t_ssl_encoding_ctx *ctx )
{
	int    i = 2; // argv[1] = command
	t_list *tmp;
	char *file;
	int fd;
	int exit_code;

	while ( i < argc )
	{
		if ( argv[i][0] == '-' )
		{
			if ( ft_strcasecmp( argv[i], "-e" ) == 0 )
				ctx->flags |= 1 << FLAG_E;
			else if ( ft_strcasecmp( argv[i], "-d" ) == 0 )
				ctx->flags |= 1 << FLAG_D;
			else if ( ft_strcasecmp( argv[i], "-i" ) == 0 )
			{
				if ( i + 1 >= argc )
				{
					ft_putstr_fd( "ft_ssl: option requires an argument -- s\n", 2 );
					print_help();
					return ( 0 );
				}

				tmp = ft_lstnew( argv[++i] );
				if ( !tmp )
				{
					print_internal_error( "ft_lstnew()" );
					return ( 0 );
				}
				ft_lstadd_back( &ctx->inf, tmp );	
			}
			else if ( ft_strcasecmp( argv[i], "-o" ) == 0 )
			{
				if ( i + 1 >= argc )
				{
					ft_putstr_fd( "ft_ssl: option requires an argument\n", 2 );
					print_help();
					return ( 0 );
				}

				tmp = ft_lstnew( argv[++i] );
				if ( !tmp )
				{
					print_internal_error( "ft_lstnew()" );
					return ( 0 );
				}
				ft_lstadd_back( &ctx->outf, tmp );
			}
			else
			{
				print_invalid_flag( argv[i] );
				print_help();
				return ( 0 );
			}
		}
		++i;
	}

	if ( ctx->inf )
	{
		file = ( char * )ft_lstlast( ctx->inf )->content;
		fd = open( file, O_RDONLY );
		if ( fd == -1 )
		{
			ft_putstr_fd( file, 2 );
			ft_putstr_fd( ": could not be opened", 2 );
			return ( 0 );
		}
		exit_code = get_content_fd( fd, &(ctx->input), &(ctx->len) );
		close( fd );
		return ( exit_code );
	}

	else
	{
		if ( !get_content_fd( 0, &(ctx->input), &(ctx->len) ) )
			return ( 0 );
	}

	return ( 1 );
}

static void free_ssl_encoding_ctx( t_ssl_encoding_ctx *ctx )
{
	ft_lstfree( &ctx->inf );
	ft_lstfree( &ctx->outf );
	if ( ctx->input )
		free( ctx->input );
}

#include <stdio.h>
int encoding_wrapper( int argc, char **argv, t_ssl_cmd *cmd )
{
	int exit_code;
	t_ssl_encoding_ctx ctx;
	size_t len;
	uint8_t *text;
	int fd;
	char *file;
	char *tmp;

	ft_memset( &ctx, 0, sizeof(ctx) );

	if ( !parse_input( argc, argv, &ctx ) )
	{
		free_ssl_encoding_ctx( &ctx );
		return ( 1 );
	}

	if ( ctx.outf )
	{
		file = ( char * )ft_lstlast( ctx.outf )->content;
		fd = open( file, O_WRONLY | O_TRUNC | O_CREAT, 0644 );
		if ( fd == -1 )
		{
			ft_putstr_fd( file, 2 );
			ft_putstr_fd( ": could not be opened", 2 );
			free_ssl_encoding_ctx( &ctx );
			return ( 1 );
		}
	}
	else
		fd = 1;

	if ( flag_active( ctx.flags, FLAG_D ) )
	{
		tmp = ft_strremove( ctx.input, '\n' );
		if ( !tmp )
		{
			if ( ctx.outf )
				close( fd );
			free_ssl_encoding_ctx( &ctx );
			return ( 1 );
		}
		free( ctx.input );
		ctx.input = tmp;

		len = 4 * ((ctx.len + 2) / 3) + 1;
		ctx.len = ft_strlen(ctx.input);
		text = malloc( sizeof(char) * len );
		exit_code = cmd->encoding.decode_func( ( const uint8_t * )ctx.input, ctx.len, text );
		if ( exit_code )
		{
			if ( ctx.outf )
				close( fd );
			free_ssl_encoding_ctx( &ctx );
			return ( 1 );
		}
	}
	else
	{
		len = 4 * ((ctx.len + 2) / 3) + 1;
		text = malloc( sizeof(char) * len );
		cmd->encoding.encode_func( ( const uint8_t *)ctx.input, ctx.len, text );
	}

	ft_putendl_fd( ( char * )text, fd );

	if ( ctx.outf )
		close( fd );
	free( text );
	free_ssl_encoding_ctx( &ctx );

	return ( 0 );
}
