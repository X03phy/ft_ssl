#pragma once


/*
 * Includes
*/

#include <stdint.h> // uintX_t
#include <stddef.h> // size_t
#include "list.h"
#include "md5.h"


/*
 * Macros
*/

#define FLAG_P 0 // a enlever
#define FLAG_Q 1
#define FLAG_R 2


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

int hash_main(int argc, char **argv);
