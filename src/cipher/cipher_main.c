#include "cipher/cipher.h"

#include <string.h>  // memset()


/*
 * Macros
 */

#define CIPHER_UNKNOWN_ALGO_FORMAT \
RED \
"%s: Error: '%s' is an unknown cipher algorithm.\n" \
RST


/*
 * Functions
 */

static const t_cipher_algo *get_cipher_algo(const char *name)
{
	int i = 0;

	while (g_cipher_algos[i].name) {
		if (strcmp(g_cipher_algos[i].name, name) == 0)
			return (&g_cipher_algos[i]);
		i += 1;
	}

	return (NULL);  // This should not happen
}


int cipher_main(int argc, char **argv)
{
	t_cipher_ctx ctx;
	int          ret;

	memset(&ctx, 0, sizeof(ctx));

	ctx.algo = get_cipher_algo(argv[1]);  // Does not have to be secured
	if (!ctx.algo) {
		fprintf(stderr, CIPHER_UNKNOWN_ALGO_FORMAT, argv[0], argv[1]);
		fprintf(stderr, "\n");
		//fprintf(stderr, CIPHER_HELP_FORMAT, argv[0], argv[1]);
		return (0);
	}

	return (1);
}
