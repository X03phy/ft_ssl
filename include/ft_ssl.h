#ifndef FT_SSL_H
#define FT_SSL_H

#define FLAG_P 1
#define FLAG_Q 2
#define FLAG_R 4
#define FLAG_S 8

typedef struct s_opts {
	int  flags;
	char **strings; // tableau de chaînes après -s
	int  strings_count;
	char **files;   // tableau de fichiers
	int  files_count;
} t_opts;

void md5_wrapper( t_opts *opts );
void sha256_wrapper( t_opts *opts );
void whirlpool_wrapper( t_opts *opts );

#endif
