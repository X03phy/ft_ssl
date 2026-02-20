#pragma once


/*
 * Includes
 */

#include "utils/colors.h"
#include <stdint.h> // uintX_t
#include <stddef.h> // size_t
#include "utils/list.h"
#include "hash/md5.h"


/*
 * Macros
 */

#define FLAG_H 0
#define FLAG_P 1
#define FLAG_Q 2
#define FLAG_R 3

#define HASH_HELP_FORMAT \
BOLD CYN "Usage:\n" RST \
"  %s %s [flags] [files]\n" \
BOLD CYN "\nFlags:\n" RST \
"  -h, --help          Display this help message and exit\n" \
"  -p, --append        Read from STDIN, echo to STDOUT and append digest\n" \
"  -q, --quiet         Suppress all normal output\n" \
"  -r, --reverse       Reverse the output format\n" \
"  -s, --string [str]  Compute digest of the given string\n"


/*
 * Enums
 */

typedef enum e_hash_input_type {
	HASH_INPUT_STDIN,
	HASH_INPUT_STRING,
	HASH_INPUT_FILE
} e_hash_input_type;


/*
 * Structures
 */

typedef struct s_hash_algo {
	const char *name;
	int        (*init)(void *ctx);
	int        (*update)(void *ctx, const uint8_t *data, size_t len);
	int        (*final)(uint8_t *out, void *ctx);
	size_t     ctx_size;
	size_t     digest_size;
} t_hash_algo;


typedef struct s_hash_input
{
	e_hash_input_type type;
	char              *data; // string ou filename
}   t_hash_input;


typedef struct s_hash_ctx
{
	const t_hash_algo *algo;
	void              *algo_ctx; // contexte réel (md5/sha256)
	int               flags;     // -p -q -r -s
	t_list            *inputs; // flags arguments and files
} t_hash_ctx;


/*
 * Global variables
 */

static const t_hash_algo g_hash_algos[] = {
	{
		"md5",
		md5_init_wrap,
		md5_update_wrap,
		md5_final_wrap,
		sizeof(t_md5_ctx),
		16
	},	{NULL, NULL, NULL, NULL, 0, 0}
};


/*
 * Prototypes
 */

/* hash_main.c */
int hash_main(int argc, char **argv);

/* parse_input */
void print_hash(t_hash_ctx *ctx, t_hash_input *input, uint8_t *digest);
int process_inputs(t_hash_ctx *hctx);
int parse_inputs(t_hash_ctx *hctx, int argc, char **argv);
