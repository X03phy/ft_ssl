#include "ft_ssl.h"
#include "hash.h"

int hash_wrapper( int argc, char **argv, t_ssl_cmd *cmd )
{
	uint8_t hash[cmd->hash.hash_size];
	t_ssl_hash_ctx ctx;
	
	ft_memset( &ctx, 0, sizeof(ctx) );

	if ( !parse_input( argc, argv, &ctx ) )
		return ( 0 );

	cmd->hash.hash_func( ( const uint8_t * )ctx.input, ctx.len, hash );

	print_hash( hash, cmd->hash.hash_size );
	printf( "\n" );

	while ( ctx.strings )
	{
		cmd->hash.hash_func( ( const uint8_t * )ctx.strings->content, ctx.len, hash );

		print_hash( hash, cmd->hash.hash_size );
		printf( "\n" );

		ctx.strings = ctx.strings->next;
	}

	return ( 1 );
}
