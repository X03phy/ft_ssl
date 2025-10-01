#ifndef FT_SSL_H
#define FT_SSL_H

/* For uintX_t */
#include <stdint.h>

/* For size_t */
#include <stddef.h>


/* Enums */
typedef enum e_cmd_type {
	CMD_HASH,
	CMD_ENCODING,
	CMD_ENCRYPTION,
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
			void ( *encode_func )( const uint8_t *, size_t, uint8_t * );
			int ( *decode_func )( const uint8_t *, size_t, uint8_t * );
		} encoding;
		
	};
} t_ssl_cmd;


/* Function pointer type for commands */
typedef int ( *t_ssl_wfunc )( int, char **, t_ssl_cmd * );


/* Global Variables */
extern t_ssl_cmd g_cmds[];


/* Prototypes */
/* Clear */

/* Print */
void print_help( void );
void print_invalid_command( const char *cmd );
void print_invalid_flag( const char *flag );
void print_internal_error( const char *func );
void print_hash( uint8_t *hash, int len );
void print_hash_input( const char *input, const char *name, int beginning, int quotes );
void print_invalid_file( const char *file );

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
