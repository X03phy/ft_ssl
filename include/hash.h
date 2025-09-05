#ifndef HASH_H
#define HASH_H

#include "libft.h"
#include <stdio.h>


/* Macros */
#define FLAG_P 0
#define FLAG_Q 1
#define FLAG_R 2


/* Structures */
typedef struct s_ssl_hash_ctx {
	int    flags;
	char   *input;
	size_t len;
	t_list *strings; // tableau de chaînes après -s
	t_list *files;   // tableau de fichiers
} t_ssl_hash_ctx;

/* Prototypes */
int parse_input( int argc, char **argv, t_ssl_hash_ctx *ctx );


#endif
