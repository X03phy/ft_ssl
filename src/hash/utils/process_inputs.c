#include "hash/hash.h"
#include <stdint.h> // uintX_t
#include <unistd.h> // ssize_t, read(), close()
#include <fcntl.h>  // open(), O_RDONLY
#include <stdio.h>  // perror()
#include <stddef.h> // size_t
#include <string.h> // strlen()
#include <stdlib.h> // malloc(), free()


/*
 * Macros
 */

#define BUFFER_SIZE 1024


/*
 * Functions
 */


#include <stdlib.h>
#include <string.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	s = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	if (!s)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		s[i + j] = s2[j];
		j++;
	}
	s[i + j] = '\0';
	return (s);
}

int get_content_fd( int fd, char **lineptr, size_t *n )
{
	*n = 0;

	*lineptr = calloc( 1, sizeof(char) );
	if ( !*lineptr )
	{
		return ( 0 );
	}

	int  r;
	char buf[43];
	char *tmp;

	while ( 1 )
	{
		r = read( fd, buf, 42 );
		if ( r == -1 ) {
			free( *lineptr );
			return ( 0 );
		}

		if ( r == 0 )
			break ;

		*n += r;
		buf[r] = '\0';

		tmp = *lineptr;
		*lineptr = ft_strjoin( *lineptr, buf );
		free( tmp );
		if ( !*lineptr )
		{
			return ( 0 );
		}
	}

	return ( 1 );
}

#include <stdio.h>
static int process_stdin(t_hash_ctx *hctx)
{
	char *line;
	size_t total_len;
	uint8_t      *digest;

	digest = malloc(hctx->algo->digest_size);

	get_content_fd(0, &line, &total_len);
	printf("line = %s\n", line);
	hctx->algo->update(hctx->algo_ctx, (uint8_t *)line, total_len);
	hctx->algo->final(digest, hctx->algo_ctx);
	size_t i = 0;

	while (i < hctx->algo->digest_size) {
		printf("%02x", digest[i]);
		i += 1;
	}
	printf("\n");
	return (1);
}


static int process_file(t_hash_ctx *hctx, const char *filename)
{
	int     fd, ret;
	ssize_t bytes_read;
	uint8_t buffer[BUFFER_SIZE];

	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		perror(filename);
		return (0);
	}

	ret = 1;
	while (ret && (bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
		ret = hctx->algo->update(hctx->algo_ctx, buffer, bytes_read);

	if (!ret || bytes_read < 0) {
		perror(filename);
		close(fd);
		return (0);
	}

	close(fd);
	return (1);
}


static int process_string(t_hash_ctx *hctx, const char *str) // check update
{
	size_t len;

	len = strlen(str);
	hctx->algo->update(hctx->algo_ctx, (const uint8_t *)str, len);

	return (1);
}


static int process_input_dispatch(t_hash_ctx *hctx, t_hash_input *input)
{
	switch (input->type) {
		case HASH_INPUT_FILE:
			return (process_file(hctx, input->data));
		case HASH_INPUT_STRING:
			return (process_string(hctx, input->data));
		default:
			return (0);
	}
}


int process_inputs(t_hash_ctx *hctx)
{
	t_list       *node;
	t_hash_input *input;
	uint8_t      *digest;

	digest = malloc(hctx->algo->digest_size);
	if (!digest) {
		perror("malloc() failed");
		return (0);
	}

	node = hctx->inputs;
	if ((hctx->flags & (1 << FLAG_P)) || !node) {
		hctx->algo->init(hctx->algo_ctx);
		if (!process_stdin(hctx))
			return (0);
	}

	while (node) {
		input = (t_hash_input *)node->data;

		hctx->algo->init(hctx->algo_ctx);

		if (!process_input_dispatch(hctx, input))
			return (0);

		hctx->algo->final(digest, hctx->algo_ctx);
		print_hash(hctx, input, digest);

		node = node->next;
	}

	free(digest);
	return (1);
}
