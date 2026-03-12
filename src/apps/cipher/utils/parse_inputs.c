// #include "hash/hash.h"

// #include "utils/colors.h"
// #include "utils/list.h"

// #include <stdlib.h>  // malloc(), free(), NULL
// #include <stdio.h>   // perror(), fprintf(), stderr
// #include <string.h>  // strcmp()


// /*
//  * Macros
//  */

// #define HASH_INVALID_OPTION_FORMAT \
// RED \
// "%s %s: Error: invalid option '%s'\n" \
// RST

// #define HASH_EXPECTING_ARGUMENT_AFTER_FLAG_FORMAT \
// RED \
// "%s %s: Error: expecting argument after '%s'\n" \
// RST


// /*
//  * Functions
//  */

// static int add_input(t_cipher_ctx *ctx, const e_cipher_input_type type, char *data)
// {
// 	t_cipher_input *input;
// 	t_list       *new;

// 	input = malloc(sizeof(t_cipher_input));
// 	if (!input) {
// 		perror("malloc failed");
// 		return (0);
// 	}

// 	input->type = type;
// 	input->data = data;

// 	new = list_new(input);
// 	if (!new) {
// 		perror("list_new() failed");
// 		free(input);
// 		return (0);
// 	}

// 	list_push_back(&ctx->inputs, new);

// 	return (1);
// }


// static void print_error(const char *format, char **argv, int i)
// {
// 	fprintf(stderr, format, argv[0], argv[1], argv[i]);
// 	fprintf(stderr, "\n");
// 	fprintf(stderr, CIPHER_HELP_FORMAT, argv[0], argv[1]);
// }


// static int parse_flag(t_cipher_ctx *ctx, int *i, int argc, char **argv)
// {
// 	if (strcmp("-h", argv[*i]) == 0 ||
// 	    strcmp("--help", argv[*i]) == 0) {
// 		ctx->flags |= 1 << CIPHER_FLAG_H;
// 	} else if ((strcmp("-a", argv[*i]) == 0) ||
// 	           (strcmp("--append", argv[*i]) == 0)) {
// 		ctx->flags |= 1 << CIPHER_FLAG_A;
// 	} else if ((strcmp("-d", argv[*i]) == 0) ||
// 	           (strcmp("--decrypt", argv[*i]) == 0)) {
// 		ctx->flags |= 1 << CIPHER_FLAG_D;
// 	} else if ((strcmp("-e", argv[*i]) == 0) ||
// 	           (strcmp("--encrypt", argv[*i]) == 0)) {
// 		ctx->flags |= 1 << CIPHER_FLAG_E;
// 	} else if ((strcmp("-i", argv[*i]) == 0) ||
// 	           (strcmp("--infile", argv[*i]) == 0)) {
// 		ctx->flags |= 1 << CIPHER_FLAG_I;
// 	} else if ((strcmp("-k", argv[*i]) == 0) ||
// 	           (strcmp("--key", argv[*i]) == 0)) {
// 		ctx->flags |= 1 << CIPHER_FLAG_K;
// 	} else if ((strcmp("-o", argv[*i]) == 0) ||
// 	           (strcmp("--outfile", argv[*i]) == 0)) {
// 		ctx->flags |= 1 << CIPHER_FLAG_I;
// 	} else if ((strcmp("-p", argv[*i]) == 0) ||
// 	           (strcmp("--passsword", argv[*i]) == 0)) {

// 		*i += 1;

// 	} else {
// 		print_error(CIPHER_INVALID_OPTION_FORMAT, argv, *i);
// 		return (0);
// 	}

// 	return (1);
// }


// int parse_inputs(t_cipher_ctx *ctx, int argc, char **argv)
// {
// 	int i = 2;

// 	while (i < argc) {
// 		if (argv[i][0] == '-') {
// 			if (!parse_flag(ctx, &i, argc, argv))
// 				return (0);
// 		} else {
// 			if (!add_input(ctx, HASH_INPUT_FILE, argv[i]))
// 				return (0);
// 		}
// 		i += 1;
// 	}

// 	return (1);
// }
