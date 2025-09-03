#ifndef FT_SSL_H
#define FT_SSL_H

#include "libft.h"

/* Macros */
#define FLAG_P 0
#define FLAG_Q 1
#define FLAG_R 2

/* Structures */
/* Options */
typedef struct s_opts {
	int    flags;
	t_list *strings; // tableau de chaînes après -s
	int    strings_count;
	t_list *files;   // tableau de fichiers
	int    files_count;
} t_opts;

/* Function pointer type for commands */
typedef void ( *t_cmd_func )( t_opts * );

typedef struct s_cmd {
	char             *name;
	const t_cmd_func func;
} t_cmd;

/* Global Variables */
extern t_cmd g_cmds[];

/* Prototypes */
/* Clear */
void opts_clear( t_opts *opts );

/* Print */
void print_help( void );
void print_invalid_command( char *cmd );
void print_invalid_flag( char *flag );
void print_func_failed( char *func );

/* Parsing */
t_cmd_func get_cmd( char *cmd );
int        parse_input( int argc, char **argv, t_opts *opts );

/* Wrappers */
void md5_wrapper( t_opts *opts );
void sha256_wrapper( t_opts *opts );
void whirlpool_wrapper( t_opts *opts );

#endif
