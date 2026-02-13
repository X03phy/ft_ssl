#include "hash.h"
#include "colors.h"
#include "list.h"
#include <string.h> // strcmp()
#include <stdio.h> // NULL, fprintf(), printf()
#include <stdlib.h> // malloc(), free()
#include <fcntl.h> // open()
#include <unistd.h> // read()


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

	return (NULL); // -> N'arrivera jamais
}


int hash_main(int argc, char **argv)
{
	int        ret;
	t_hash_ctx hctx;

	memset(&hctx, 0, sizeof(hctx));

	hctx.algo = get_hash_algo(argv[1]); // Pourra etre fourni en argument de cette fct -> opti

	ret = parse_inputs(&hctx, argc, argv);
	if (!ret)
		return (0);

	hctx.algo_ctx = malloc(hctx.algo->ctx_size);
	if (!hctx.algo_ctx) {
		perror("malloc() failed");
		return (0);
	}

	process_inputs(&hctx);

	ret = 0;
	return (ret);
}
