#include "hash.h"
#include <string.h> // strcmp(), memset()
#include <stdio.h>  // NULL, fprintf(), perror()
#include <stdlib.h> // malloc(), free()


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

	return (NULL);
}


int hash_main(int argc, char **argv)
{
	int        ret;
	t_hash_ctx hctx;

	memset(&hctx, 0, sizeof(hctx));

	hctx.algo = get_hash_algo(argv[1]);
	if (hctx.algo == NULL) {
		fprintf(stderr, "%s: Error: '%s' is an unknown hash algorithm", argv[0], argv[1]);
		return (0);
	}

	ret = parse_inputs(&hctx, argc, argv);
	if (!ret) {
		// free_hash_ctx(hctx);
		return (0);
	}

	hctx.algo_ctx = malloc(hctx.algo->ctx_size);
	if (!hctx.algo_ctx) {
		perror("malloc() failed");
		return (0);
	}

	ret = process_inputs(&hctx);

	free(hctx.algo_ctx);
	return (!ret);
}
