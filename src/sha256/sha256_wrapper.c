#include "ft_ssl.h"
#include "sha256.h"

void sha256_wrapper( t_opts *opts )
{
	char *line;
	size_t  len;
	get_next_line( &line, &len );
	sha256();
	(void)opts;
}
