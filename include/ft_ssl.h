#ifndef FT_SSL_H
#define FT_SSL_H

#include "libft.h"

/* Macros */
#define FLAG_P 0
#define FLAG_Q 1
#define FLAG_R 2

/* Structures */
/* Options */
typedef struct s_ssl_ctx {
	int    flags;
	char   *input;
	size_t len;
	t_list *strings; // tableau de chaînes après -s
	t_list *files;   // tableau de fichiers
} t_ssl_ctx;

/* Function pointer type for commands */
typedef void ( *t_cmd_func )( t_ssl_ctx * );

typedef struct s_cmd {
	char             *name;
	const t_cmd_func func;
} t_cmd;

/* Global Variables */
extern t_cmd g_cmds[];

/* Prototypes */
/* Clear */
void ssl_ctx_clear( t_ssl_ctx *ssl_ctx );

/* Print */
void print_help( void );
void print_invalid_command( char *cmd );
void print_invalid_flag( char *flag );
void print_func_failed( char *func );
void print_hash( uint8_t *hash, int len );

/* Utils */
int get_input_fd( int fd, char **lineptr, size_t *n );

/* Parsing */
t_cmd_func get_cmd( char *cmd );
int        parse_input( int argc, char **argv, t_ssl_ctx *ssl_ctx );

/* Wrappers */
void md5_wrapper( t_ssl_ctx *ssl_ctx );
void sha256_wrapper( t_ssl_ctx *ssl_ctx );
void whirlpool_wrapper( t_ssl_ctx *ssl_ctx );

#endif
