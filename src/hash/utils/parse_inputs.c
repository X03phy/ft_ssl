#include "hash/hash.h"

#include "utils/colors.h"
#include "utils/list.h"

#include <stdlib.h>  // malloc(), free(), NULL
#include <stdio.h>   // perror(), fprintf(), stderr
#include <string.h>  // strcmp()


/*
 * Macros
 */

#define HASH_INVALID_OPTION_FORMAT \
RED \
"%s %s: Error: invalid option '%s'\n" \
RST

#define HASH_EXPECTING_ARGUMENT_AFTER_FLAG_FORMAT \
RED \
"%s %s: Error: expecting argument after '%s'\n" \
RST


/*
 * Functions
 */

static int add_input(t_hash_ctx *ctx, const e_hash_input_type type, char *data)
{
	t_hash_input *input;
	t_list       *new;

	input = malloc(sizeof(t_hash_input));
	if (!input) {
		perror("malloc failed");
		return (0);
	}

	input->type = type;
	input->data = data;

	new = list_new(input);
	if (!new) {
		perror("list_new() failed");
		free(input);
		return (0);
	}

	list_push_back(&ctx->inputs, new);

	return (1);
}


int parse_inputs(t_hash_ctx *ctx, int argc, char **argv)
{
	int i = 2;

	while (i < argc) {
		if (argv[i][0] == '-') {
			if ((argv[i][1] == 'h' && argv[i][2] == '\0') || strcmp("--help", argv[i]) == 0) {
				ctx->flags |= 1 << FLAG_H;
				return (1);
			} else if ((argv[i][1] == 'p' && argv[i][2] == '\0') || strcmp("--append", argv[i]) == 0) {
				ctx->flags |= 1 << FLAG_P;
			} else if ((argv[i][1] == 'q' && argv[i][2] == '\0') || strcmp("--quiet", argv[i]) == 0) {
				ctx->flags |= 1 << FLAG_Q;
			} else if ((argv[i][1] == 'r' && argv[i][2] == '\0') || strcmp("--reverse", argv[i]) == 0) {
				ctx->flags |= 1 << FLAG_R;
			} else if ((argv[i][1] == 's' && argv[i][2] == '\0') || strcmp("--string", argv[i]) == 0) {
				if (i + 1 >= argc) {
					fprintf(stderr, HASH_EXPECTING_ARGUMENT_AFTER_FLAG_FORMAT, argv[0], argv[1], argv[i]);
					fprintf(stderr, "\n");
					fprintf(stderr, HASH_HELP_FORMAT, argv[0], argv[1]);
					return (0);
				}
				i += 1;
				if (!add_input(ctx, HASH_INPUT_STRING, argv[i]))
					return (0);
			} else {
				fprintf(stderr, HASH_INVALID_OPTION_FORMAT, argv[0], argv[1], argv[i]);
				fprintf(stderr, "\n");
				fprintf(stderr, HASH_HELP_FORMAT, argv[0], argv[1]);
				return (0);
			}
		} else {
			if (!add_input(ctx, HASH_INPUT_FILE, argv[i]))
				return (0);
		}
		i += 1;
	}

	return (1);
}
