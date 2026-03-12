#include "hash/hash.h"

#include "utils/colors.h"

#include <string.h>  // strcmp(), NULL, memset()
#include <stdio.h>   // fprintf, stderr, printf()
#include <stdlib.h>  // free(), malloc()


/*
 * Macros
 */

#define HASH_UNKNOWN_ALGO_FORMAT \
RED \
"%s: Error: '%s' is an unknown message digest algorithm.\n" \
RST


/*
 * Functions
 */

static const t_hash_algo *get_hash_algo(const char *name)
{
	int i = 0;

	while (g_hash_algos[i].name) {
		if (strcmp(g_hash_algos[i].name, name) == 0)
			return (&g_hash_algos[i]);
		i += 1;
	}

	return (NULL);  // This should not happen
}


int hash_main(int argc, char **argv)
{
	t_hash_ctx ctx;
	int        ret;

	memset(&ctx, 0, sizeof(ctx));

	ctx.algo = get_hash_algo(argv[1]);  // Does not have to be secured
	if (!ctx.algo) {
		fprintf(stderr, HASH_UNKNOWN_ALGO_FORMAT, argv[0], argv[1]);
		fprintf(stderr, "\n");
		fprintf(stderr, HASH_HELP_FORMAT, argv[0], argv[1]);
		return (0);
	}

	if (!parse_inputs(&ctx, argc, argv)) {
		list_clear(&ctx.inputs, free);
		return (0);
	}

	if (ctx.flags & (1 << FLAG_H)) {  // Add is flag active
		printf(HASH_HELP_FORMAT, argv[0], argv[1]);
		ret = 1;
		goto cleanup;
	}

	ctx.algo_ctx = malloc(ctx.algo->ctx_size);
	if (!ctx.algo_ctx) {
		perror("malloc() failed");
		ret = 0;
		goto cleanup;
	}

	ret = process_inputs(&ctx);

	free(ctx.algo_ctx);
cleanup:
	list_clear(&ctx.inputs, free);
	return (ret);
}
