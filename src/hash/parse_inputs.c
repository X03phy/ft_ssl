#include "hash.h"
#include "colors.h"
#include "list.h"
#include <stdlib.h> // malloc(), free()
#include <stdio.h> // perror(), fprintf()


/*
 * Macros
 */

#define UNRECOGNIZED_OPTION_FORMAT RED "%s: unrecognized option '%s'\n" RST // -> probablement a mettre dans le .h global (ft_ssl.h)
#define HASH_USAGE_FORMAT GRN "\nUsage: %s %s [flags] [file/string]\n" RST


/*
 * Functions
 */

static int add_input(t_hash_ctx *hctx, e_hash_input_type type, char *data)
{
	t_hash_input *hinput;
	t_list       *new;

	hinput = malloc(sizeof(t_hash_input));
	if (!hinput)
		return (0);

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


// ajouter des --help, -h, ...
int parse_inputs(t_hash_ctx *hctx, int argc, char **argv) // checker comment free !!??
{
	int ret, i;

	i = 2;
	while (i < argc) {
		if (argv[i][0] == '-') {
			if (argv[i][1] == 'q' && argv[i][2] == '\0') {
				hctx->flags |= 1 << FLAG_Q;
			} else if (argv[i][1] == 'r' && argv[i][2] == '\0') {
				hctx->flags |= 1 << FLAG_R;
			} else if (argv[i][1] == 'p' && argv[i][2] == '\0') {
				ret = add_input(hctx, HASH_INPUT_STDIN, NULL);
				if (!ret)
					return (0);
			} else if (argv[i][1] == 's' && argv[i][2] == '\0') {
				i += 1;
				if (i >= argc) {
					/* crustom error messages */
					fprintf(stderr, "invalid argument after...");
					return (0);
				}
				ret = add_input(hctx, HASH_INPUT_STRING, argv[i]);
				if (!ret)
					return (0);
			} else {
				fprintf(stderr, UNRECOGNIZED_OPTION_FORMAT, argv[0], argv[i]);  //! Ameliorer les messages
				fprintf(stderr, HASH_USAGE_FORMAT, argv[0], argv[1]);
				return (0);
			}
		} else {
			ret = add_input(hctx, HASH_INPUT_FILE, argv[i]);
			if (!ret)
				return (0);
		}
		i += 1;
	}

	return (1);
}
