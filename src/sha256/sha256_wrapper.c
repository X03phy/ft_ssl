#include "ft_ssl.h"
#include "sha256.h"

void sha256_wrapper( t_opts *opts )
{
	// char *line;
	// int  len;
	// uint8_t hash[32];

	char buf[1000];
	int r = read( 0, buf, 1000 );
	buf[r] = '\0';
	printf("%s", buf);

	// get_next_line( &line, &len, 0 );
	// printf("%s", line);
	// sha256((uint8_t *)line, ft_strlen(line), hash);
	// for (int i = 0; i < 32; i++)
	// 	printf("%02x", hash[i]);
	// free(line);
	(void)opts;
}
