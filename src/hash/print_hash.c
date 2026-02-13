#include "hash.h"
#include <stdio.h> // printf()


/*
 * Functions
 */

static void print_hex(uint8_t *digest, size_t size)
{
	size_t i = 0;

	while (i < size)
	{
		printf("%02x", digest[i]);
		i += 1;
	}
}


void print_hash(t_hash_ctx *ctx, t_hash_input *input, uint8_t *digest)
{
	if (ctx->flags & (1 << FLAG_Q)) {
		print_hex(digest, ctx->algo->digest_size);
		printf("\n");
		return ;
	}

	if (ctx->flags & (1 << FLAG_R)) {
		print_hex(digest, ctx->algo->digest_size);

		if (input->type == HASH_INPUT_STRING)
			printf(" \"%s\"", input->data);
		else if (input->type == HASH_INPUT_FILE)
			printf(" %s", input->data);

		printf("\n");
		return ;
	}

	if (input->type == HASH_INPUT_FILE)
		printf("%s(%s) = ", ctx->algo->name, input->data);
	else if (input->type == HASH_INPUT_STRING)
		printf("%s(\"%s\") = ", ctx->algo->name, input->data);
	else if (input->type == HASH_INPUT_STDIN)
		printf("(stdin) = ");

	print_hex(digest, ctx->algo->digest_size);
	printf("\n");
}
