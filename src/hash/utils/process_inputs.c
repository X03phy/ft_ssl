#include "hash/hash.h"

#include <stdint.h>  // uintX_t
#include <unistd.h>  // ssize_t, read(), close()
#include <stdio.h>   // perror()
#include <fcntl.h>   // open(), O_RDONLY
#include <stddef.h>  // size_t
#include <string.h>  // strlen()
#include <stdlib.h>  // malloc(), free()


/*
 * Macros
 */

#define BUFFER_SIZE 1024  //! Has to be a multiple of 64


/*
 * Functions
 */

static int process_stdin(uint8_t *digest, t_hash_ctx *ctx)
{
	ssize_t	     bytes_read;
	uint8_t	     buffer[BUFFER_SIZE];
	t_hash_input input;

	while ((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
		if (!ctx->algo->update(ctx->algo_ctx, buffer, bytes_read))
			return (0);
	}

	if (bytes_read < 0) {
		perror("read failed");
		return (0);
	}

	ctx->algo->final(digest, ctx->algo_ctx);

	input.type = HASH_INPUT_STDIN;
	input.data = "stdin";
	print_hash(digest, ctx, &input);

	return (1);
}


static int process_file(t_hash_ctx *ctx, const char *filename)
{
	int     fd;
	ssize_t bytes_read;
	uint8_t buffer[BUFFER_SIZE];

	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		perror(filename);
		return (0);
	}

	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
		if (!ctx->algo->update(ctx->algo_ctx, buffer, bytes_read)) {
			close(fd);
			return (0);
		}
	}

	if (bytes_read < 0) {
		perror("read() failed");
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
	if (!hctx->algo->update(hctx->algo_ctx, (const uint8_t *)str, len))
		return (0);

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
			return (0); // This should not happen
	}
}


int process_inputs(t_hash_ctx *ctx)
{
	t_list       *node;
	t_hash_input *input;
	uint8_t      *digest;

	digest = malloc(ctx->algo->digest_size);
	if (!digest) {
		perror("malloc() failed");
		return (0);
	}

	node = ctx->inputs;
	if ((ctx->flags & (1 << FLAG_P)) || !node) {
		ctx->algo->init(ctx->algo_ctx);
		if (!process_stdin(digest, ctx))
			return (0);
	}

	while (node) {
		input = (t_hash_input *)node->data;

		ctx->algo->init(ctx->algo_ctx);
		if (!process_input_dispatch(ctx, input)) {
			free(digest);
			return (0);
		}
		ctx->algo->final(digest, ctx->algo_ctx);
		print_hash(digest, ctx, input);

		node = node->next;
	}

	free(digest);
	return (1);
}
