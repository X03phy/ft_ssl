#include "hash.h"
#include "colors.h"
#include "list.h"
#include <stdlib.h> // malloc(), free(), NULL
#include <stdio.h>  // perror(), fprintf()
#include <string.h> // strcmp()


/*
 * Macros
 */

#define HASH_INVALID_OPTION_FORMAT RED "%s %s: Error: invalid option '%s'\n" RST


/*
 * Functions
 */

static int add_input(t_hash_ctx *hctx, const e_hash_input_type type, char *data)
{
	t_hash_input *hinput;
	t_list       *new;

	hinput = malloc(sizeof(t_hash_input));
	if (!hinput) {
		perror("malloc failed");
		return (0);
	}

	hinput->type = type;
	hinput->data = data;

	new = list_new(hinput);
	if (!new) {
		perror("list_new() failed");
		free(hinput);
		return (0);
	}

	list_push_back(&hctx->inputs, new);

	return (1);
}


int parse_inputs(t_hash_ctx *hctx, int argc, char **argv)
{
	int i = 2;

	while (i < argc) {
		if (argv[i][0] == '-') {
			if ((argv[i][1] == 'h' && argv[i][2] == '\0') || strcmp("--help", argv[i]) == 0) {
				hctx->flags |= 1 << FLAG_H;
			} else if ((argv[i][1] == 'p' && argv[i][2] == '\0') || strcmp("--append", argv[i]) == 0) {
				hctx->flags |= 1 << FLAG_P;
			} else if ((argv[i][1] == 'q' && argv[i][2] == '\0') || strcmp("--quiet", argv[i]) == 0) {
				hctx->flags |= 1 << FLAG_Q;
			} else if ((argv[i][1] == 'r' && argv[i][2] == '\0') || strcmp("--reverse", argv[i]) == 0) {
				hctx->flags |= 1 << FLAG_R;
			} else if ((argv[i][1] == 's' && argv[i][2] == '\0') || strcmp("--string", argv[i]) == 0) {
				if (i + 1 >= argc) {
					fprintf(stderr, RED "%s %s: Error: expecting argument after '%s'\n" RST, argv[0], argv[1], argv[i]);
					fprintf(stderr, HASH_HELP_FORMAT, argv[0], argv[1]);
					return (0);
				}
				i += 1;
				if (!add_input(hctx, HASH_INPUT_STRING, argv[i]))
					return (0);
			} else {
				fprintf(stderr, HASH_INVALID_OPTION_FORMAT, argv[0], argv[1], argv[i]);
				fprintf(stderr, HASH_HELP_FORMAT, argv[0], argv[1]);
				return (0);
			}
		} else {
			if (!add_input(hctx, HASH_INPUT_FILE, argv[i]))
				return (0);
		}
		i += 1;
	}

	return (1);
}
