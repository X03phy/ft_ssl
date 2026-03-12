#pragma once


/*
 * Includes
 */

#include "hash/hash.h"
#include "cipher/cipher.h"


/*
 * Structures
 */

typedef struct s_cmd {
	const char *name;
	int        (*func)(int argc, char *argv[]);
} t_cmd;


/*
 * Global Variables
 */

static const t_cmd g_cmds[] = {
/* Message Digest commands */
	{"md5", hash_main},
	{"sha256", hash_main},
	{"whirlpool", hash_main},
/* Cipher commands */
	// {"base64", cipher_main},
	// {"rc4", cipher_main},
	{NULL, NULL}
};
