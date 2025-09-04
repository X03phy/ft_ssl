#include "ft_ssl.h"
#include "sha256.h"

void sha256_wrapper( t_ssl_ctx *ssl_ctx )
{
	uint8_t hash[32];

	if ( ( ( 1 & ssl_ctx->flags ) != 0 ) || ( !ssl_ctx->strings && !ssl_ctx->files ) )
	{
		if (  )
		sha256( ( uint8_t * )ssl_ctx->input, ssl_ctx->len, hash );
		print_hash( hash, 32 );
	}

	while (  )
}
