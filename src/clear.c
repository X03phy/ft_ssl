#include "ft_ssl.h"

void opts_clear( t_opts *opts )
{
	ft_lstfree( &opts->strings );
	ft_lstfree( &opts->files );
}
