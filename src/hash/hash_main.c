#include "hash/hash.h"
#include "utils/colors.h"
#include <string.h> // strcmp(), memset()
#include <stdio.h>  // NULL, fprintf, printf()
#include <stdlib.h> // malloc()


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
	t_hash_ctx hctx;
	int        ret;

	memset(&hctx, 0, sizeof(hctx));

	hctx.algo = get_hash_algo(argv[1]);

	if (parse_inputs(&hctx, argc, argv)) {
		list_clear(&hctx.inputs, free);
		return (0);
	}

	if (hctx.flags & (1 << FLAG_H)) {
		printf(HASH_HELP_FORMAT, argv[0], argv[1]);
		list_clear(&hctx.inputs, free);
		return (1);
	}

	hctx.algo_ctx = malloc(hctx.algo->ctx_size);
	if (!hctx.algo_ctx) {
		perror("malloc() failed");
		list_clear(&hctx.inputs, free);
		return (0);
	}

	ret = process_inputs(&hctx);

	list_clear(&hctx.inputs, free);
	free(hctx.algo_ctx);
	return (ret);
}
