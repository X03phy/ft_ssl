#pragma once

/*
 * Includes
 */

#include <stdint.h>  // uintX_t
#include <stddef.h>  // size_t

#include "utils/colors.h"
#include "utils/list.h"

/*
 * Macros
 */

//#define FLAG_H 0
//#define FLAG_A 1
//#define FLAG_D 2
//#define FLAG_E 3
//#define FLAG_I 4
//#define FLAG_K 5
//#define FLAG_O 6
//#define FLAG_P 7
//#define FLAG_S 8
//#define FLAG_V 9


/*
 * Enums
 */

typedef enum e_cipher_input_type {
	// CIPHER_INPUT_STDIN,
	// CIPHER_INPUT_STRING,
	CIPHER_INPUT_FILE
} e_cipher_input_type;


/*
 * Structures
 */

typedef struct s_cipher_algo {
	const char *name;
	int        (*init)(void *ctx);
	int        (*update)(void *ctx, const uint8_t *data, size_t len);
	int        (*final)(uint8_t *digest, void *ctx);
	size_t     ctx_size;
	size_t     digest_size;
} t_cipher_algo;


typedef struct s_cipher_input
{
	e_cipher_input_type type;
	char                *data;  // string or filename
}   t_cipher_input;


typedef struct s_cipher_ctx
{
	const t_cipher_algo *algo;
	void              *algo_ctx;  // contexte réel (md5/sha256)
	int               flags;      // -p -q -r -s
	t_list            *inputs;    // flags arguments and files
} t_cipher_ctx;


/*
 * Global variables
 */

//static const t_cipher_algo g_hash_algos[] = {
//	{
//		"md5",
//		md5_init_wrap,
//		md5_update_wrap,
//		md5_final_wrap,
//		sizeof(t_md5_ctx),
//		16
//	},
//	{
//		"sha256",
//		sha256_init_wrap,
//		sha256_update_wrap,
//		sha256_final_wrap,
//		sizeof(t_sha256_ctx),
//		32
//	},
//	{
//		"whirlpool",
//		whirlpool_init_wrap,
//		whirlpool_update_wrap,
//		whirlpool_final_wrap,
//		sizeof(t_whirlpool_ctx),
//		64
//	},
//	{NULL, NULL, NULL, NULL, 0, 0}
//};


/*
 * Prototypes
 */

int cipher_main(int argc, char **argv);
