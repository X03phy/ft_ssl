#pragma once


/*
 * Includes
*/

#include "hash.h"


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
	{"md5", hash_main},
	{"sha256", hash_main},
	{"whirlpool", hash_main},
	// {"base64", base64_main},
	// {"rsa", rsa_main},
	{NULL, NULL}
};
