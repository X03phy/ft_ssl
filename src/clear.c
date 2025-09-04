#include "ft_ssl.h"

void ssl_ctx_clear( t_ssl_ctx *ssl_ctx )
{
	ft_lstfree( &ssl_ctx->strings );
	ft_lstfree( &ssl_ctx->files );
}
