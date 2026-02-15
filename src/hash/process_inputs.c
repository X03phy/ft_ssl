#include "hash.h"
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


static int process_stdin(t_hash_ctx *hctx)
{
	(void)hctx;
	return (1);
}


static int process_input_dispatch(t_hash_ctx *hctx, t_hash_input *input)
{
	switch (input->type)
	{
		case HASH_INPUT_FILE:
			return (process_file(hctx, input->data));
		case HASH_INPUT_STRING:
			return (process_string(hctx, input->data));
		case HASH_INPUT_STDIN:
			return (process_stdin(hctx));
		default:
			return (0);
	}
}


int process_inputs(t_hash_ctx *hctx)
{
	t_list       *node;
	t_hash_input *input;
	uint8_t      *digest;
	int          ret;

	// if (!hctx->inputs)
	// 	return (process_stdin(hctx));

	digest = malloc(hctx->algo->digest_size);
	if (!digest) {
		perror("malloc() failed");
		return (0);
	}

	node = hctx->inputs;
	while (node) {
		input = (t_hash_input *)node->data;

		hctx->algo->init(hctx->algo_ctx);

		ret = process_input_dispatch(hctx, input);
		if (!ret)
			return (0);

		hctx->algo->final(digest, hctx->algo_ctx);
		print_hash(hctx, input, digest);

		node = node->next;
	}

	free(digest);
	return (1);
}
