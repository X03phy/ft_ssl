#include "hash/hash.h"
#include <string.h> // strcmp(), memset()
#include <stdio.h>  // NULL, printf()
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


void free_hash_ctx(t_hash_ctx *hctx)
{
	t_list *node, *next;

	node = hctx->inputs;
	while (node) {
		next = node->next;
		free(node->data);
		free(node);
		node = next;
	}

	if (hctx->algo_ctx)
		free(hctx->algo_ctx);
}


int hash_main(int argc, char **argv)
{
	int        ret;
	t_hash_ctx hctx;

	memset(&hctx, 0, sizeof(hctx));

	hctx.algo = get_hash_algo(argv[1]);
	if (hctx.algo == NULL)
		return (0);

	ret = parse_inputs(&hctx, argc, argv);
	if (!ret) {
		free_hash_ctx(&hctx);
		return (0);
	}

	if (hctx.flags & (1 << FLAG_H))
		printf(HASH_HELP_FORMAT, argv[0], argv[1]);

	hctx.algo_ctx = malloc(hctx.algo->ctx_size);
	if (!hctx.algo_ctx) {
		perror("malloc() failed");
		free_hash_ctx(&hctx);
		return (0);
	}

	ret = process_inputs(&hctx);

	free_hash_ctx(&hctx);
	return (ret);
}
