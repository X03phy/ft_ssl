#ifndef FT_SSL_H
#define FT_SSL_H


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

typedef enum e_cmd_type {
	EVP_CMD_HASH,
	EVP_CMD_ENCODING,
	EVP_CMD_CIPHER
} e_cmd_type;


/*
 * Structures
*/

typedef struct s_evp_md {

} t_evp_md;

/* Commands */
typedef struct s_evp_cmd {
	const char *name;
	e_cmd_type type;
	union {
		struct {
			size_t hash_size;
			void   (*hash_func)(const uint8_t *, size_t, uint8_t *);
		} hash;
		struct {
			void (*encode_func)(const uint8_t *, size_t, uint8_t *);
			int  (*decode_func)(const uint8_t *, size_t, uint8_t *);
		} encoding;
	};
} t_evp_cmd;


/* Function pointer type for commands */
typedef int (*t_ssl_wfunc)(int, char **, t_ssl_cmd *);


/*
 * Global Variables
*/

extern t_ssl_cmd g_cmds[];


/*
 * Prototypes
*/

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
