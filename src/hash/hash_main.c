#include "hash.h"
#include "colors.h"
#include "list.h"
#include <string.h> // strcmp()
#include <stdio.h> // NULL, fprintf(), printf()
#include <stdlib.h> // malloc(), free()
#include <fcntl.h> // open()


/*
 * Macros
*/

#define UNRECOGNIZED_OPTION_FORMAT RED "%s: unrecognized option '%s'\n" RST // -> probablement a mettre dans le .h global (ft_ssl.h)
#define HASH_USAGE_FORMAT GRN "\nUsage: %s %s [flags] [file/string]\n" RST


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
static int parse_inputs(t_hash_ctx *hctx, int argc, char **argv) // checker comment free !!??
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



static int process_stdin(t_hash_ctx *hctx)
{
	(void)hctx;
	return (1);
}


int process_string(t_hash_ctx *hctx, const char *str)
{
	size_t len;

	len = strlen(str);

	hctx->algo->update(hctx->algo_ctx, (const uint8_t *)str, len);

	return (1);
}


static int process_file(t_hash_ctx *hctx, const char *str)
{
	int fd;

	fd = open(str, O_RDONLY);
	if (fd < 0) {
		perror(hctx->algo->name);
		return (0);
	}


	(void)hctx;
	return (1);
}


static void print_hex(uint8_t *digest, size_t size)
{
	size_t i = 0;

	while (i < size)
	{
		printf("%02x", digest[i]);
		i++;
	}
}


void print_hash(t_hash_ctx *ctx, t_hash_input *input, uint8_t *digest)
{
	int is_quiet = ctx->flags & (1 << FLAG_Q);
	int is_reverse = ctx->flags & (1 << FLAG_R);

	/* QUIET MODE */
	if (is_quiet) {
		print_hex(digest, ctx->algo->digest_size);
		printf("\n");
		return ;
	}

	/* REVERSE MODE */
	if (is_reverse) {
		print_hex(digest, ctx->algo->digest_size);

		if (input->type == HASH_INPUT_STRING)
			printf(" \"%s\"", input->data);
		else if (input->type == HASH_INPUT_FILE)
			printf(" %s", input->data);

		printf("\n");
		return ;
	}

	/* NORMAL MODE */

	if (input->type == HASH_INPUT_STRING)
		printf("%s (\"%s\") = ", ctx->algo->name, input->data);
	else if (input->type == HASH_INPUT_FILE)
		printf("%s (%s) = ", ctx->algo->name, input->data);
	else if (input->type == HASH_INPUT_STDIN)
		printf("(stdin)= ");

	print_hex(digest, ctx->algo->digest_size);
	printf("\n");
}


int process_inputs(t_hash_ctx *hctx)
{
	t_list       *node;
	t_hash_input *input;
	uint8_t      digest[hctx->algo->digest_size];
	int          ret;

	node = hctx->inputs; // handle if no inputs
	while (node) {
		input = (t_hash_input *)node->data;

		hctx->algo->init(hctx->algo_ctx);

		switch (input->type) {
			case HASH_INPUT_FILE:
				ret = process_file(hctx, input->data);
				break;
			case HASH_INPUT_STDIN:
				ret = process_stdin(hctx);
				break;
			case HASH_INPUT_STRING:
				ret = process_string(hctx, input->data);
				break;
		}

		if (!ret)
			return (0);

		hctx->algo->final(digest, hctx->algo_ctx);

		print_hash(hctx, input, digest);

		node = node->next;
	}

	return (1);
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

	// free(hctx.algo);

	return (ret);
}
