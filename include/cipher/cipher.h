#pragma once

/*
 * Includes
 */

#include <stdint.h>  // uintX_t
#include <stddef.h>  // size_t

#include "utils/colors.h"
#include "utils/list.h"

#include "cipher/rc4.h"


/*
 * Macros
 */

#define CIPHER_FLAG_H 0
#define CIPHER_FLAG_A 1
#define CIPHER_FLAG_D 2
#define CIPHER_FLAG_E 3
#define CIPHER_FLAG_I 4
#define CIPHER_FLAG_K 5
#define CIPHER_FLAG_O 6
#define CIPHER_FLAG_P 7
#define CIPHER_FLAG_S 8
#define CIPHER_FLAG_V 9


/*
 * Enums
 */

typedef enum e_cipher_input_type {
	//CIPHER_INPUT_STDIN,
	//CIPHER_INPUT_STRING,
	CIPHER_INPUT_FILE
} e_cipher_input_type;


/*
 * Structures
 */

typedef struct s_cipher_algo {
	const char *name;
	union {
		struct {
			int (*init)(void *ctx, const uint8_t *key, const size_t len);
			int (*crypt)(void *ctx, uint8_t *out, const uint8_t *in, size_t len);
			//int (*final)(void *ctx, uint8_t *out);
		} cipher;
		struct {
			int (*encode)(uint8_t *out, const uint8_t *in, size_t len);
			int (*decode)(uint8_t *out, const uint8_t *in, size_t len);
		} codec;
	};
	size_t     ctx_size;
} t_cipher_algo;


typedef struct s_cipher_input {
	e_cipher_input_type type;
	char                *data;
} t_cipher_input;


typedef struct s_cipher_ctx {
	const t_cipher_algo *algo;
	void                *algo_ctx;
	int                 flags;
	t_list              *inputs;
} t_cipher_ctx;


/*
 * Global variables
 */

static const t_cipher_algo g_cipher_algos[] = {
/* Cipher algorithms */
	{
		"rc4",
		.cipher = {
			.init = rc4_init_wrap,
			.crypt = rc4_crypt_wrap
		},
		0
	},


/* Codec algorithms */




	{NULL, {0}, 0}
};


/*
 * Prototypes
 */

/* cipher/cipher_main.c */
int cipher_main(int argc, char **argv);
