#pragma once


/*
 * Includes
*/

#include <stdint.h> // uintX_t
#include <stddef.h> // size_t


/*
 * Macros
*/

#define HELP_FORMAT "\n" \
                    "Message Digest commands:\n" \
                    "md5\n" \
                    "sha256\n" \
                    "whirlpool\n" \
                    "\n" \
                    "Flags:\n" \
                    "-p -q -r -s\n" \
                    "\n" \
                    "Cipher commands:\n" \
                    "base64\n" \
                    "\n"


/*
 * Enums
*/

typedef enum e_func_type {
	ft_none,
	ft_general,
	ft_md,
	ft_cipher,
	ft_pkey,
	ft_md_alg,
	ft_cipher_alg
} e_func_type;

/*
 * Structures
*/

typedef struct s_options {
	const char *name;
	int        retval;
	int        valtype;
	const char *helpstr;
} t_options;


typedef struct s_function {
	e_func_type     type;
	const char      *name;
	int             (*func)(int argc, char *argv[]);
	const t_options *help;
} t_function;


// /* Commands */
// typedef struct s_evp_cmd {
// 	const char *name;
// 	e_cmd_type type;
// 	union {
// 		struct {
// 			size_t hash_size;
// 			void   (*hash_func)(const uint8_t *, size_t, uint8_t *);
// 		} hash;
// 		struct {
// 			void (*encode_func)(const uint8_t *, size_t, uint8_t *);
// 			int  (*decode_func)(const uint8_t *, size_t, uint8_t *);
// 		} encoding;
// 	};
// } t_evp_cmd;


/* Function pointer type for commands */
// typedef int (*t_ssl_wfunc)(int, char **, t_ssl_cmd *);


/*
 * Global Variables
*/

// extern t_ssl_cmd g_cmds[];


/*
 * Prototypes
*/

/* Utils */
int get_content_fd( int fd, char **lineptr, size_t *n );
static inline int flag_active( int n, int f )
{
	return ( ( n >> f ) & 1 );
}


/* Parsing */
t_ssl_wfunc parse_cmd( t_ssl_cmd *cmd, char *arg );

/* Wrapper */
int hash_wrapper( int argc, char **argv, t_ssl_cmd *cmd );
int encoding_wrapper( int argc, char **argv, t_ssl_cmd *cmd );

#endif
