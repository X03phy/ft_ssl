#include "ft_ssl.h"
#include <stdio.h>
#include <stdlib.h>
int encoding_wrapper( int argc, char **argv, t_ssl_cmd *cmd )
{
	const char *line = "yeah";
	size_t n = 4;
	uint8_t *yeah = NULL;
	size_t out_len;

	(void)argc;
	(void)argv;


	out_len = 4 * ((n + 2) / 3) + 1;
    yeah = malloc(out_len);

	cmd->encoding.encode_func( ( const uint8_t *)line, n, yeah );

	printf( "%s\n", yeah );
	return ( 1 );
}
