#ifndef FT_SSL_H
#define FT_SSL_H

#include "color_code.h"
#include "libft.h"


/* Enums */
typedef enum e_cmd_type {
	CMD_HASH,
	CMD_CIPHER
} t_cmd_type;

/* Structures */
/* Commands */
typedef struct s_ssl_cmd {
	const char *name;
	t_cmd_type type;
	union {
		struct {
			size_t hash_size;
			void ( *hash_func )( const uint8_t *, size_t, uint8_t * );
		} hash;
		struct {
			int key_size;
			void ( *encrypt )( const uint8_t *, size_t, const uint8_t *, uint8_t * );
			void ( *decrypt )( const uint8_t *, size_t, const uint8_t *, uint8_t * );
		} cipher;
	};
} t_ssl_cmd;


/* Function pointer type for commands */
typedef int ( *t_ssl_wfunc )( int, char **, t_ssl_cmd * );


/* Global Variables */
extern t_ssl_cmd g_cmds[];


int hash_wrapper( int argc, char **argv, t_ssl_cmd *cmd );

/* Prototypes */
/* Clear */

/* Print */
void print_help( void );
void print_invalid_command( char *cmd );
void print_invalid_flag( char *flag );
void print_func_failed( char *func );
void print_hash( uint8_t *hash, int len );
void print_algo_input( char *algo, const char *input );

/* Utils */
int get_input_fd( int fd, char **lineptr, size_t *n );

/* Parsing */
t_ssl_wfunc parse_cmd( t_ssl_cmd *cmd );

/* Wrapper */


#endif
