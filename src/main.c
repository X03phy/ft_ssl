#include "ft_ssl.h"
#include "colors.h" // COLORS
#include <string.h> // memset(), strcmp()
#include <stdio.h> // fprintf(), stderr


#define USAGE_FORMAT "usage: %s command [flags] [file/string]\n"
#define INVALID_COMMAND_FORMAT RED "%s: Error: '%s' is an invalid command\n" RST






#define LHASH_OF(type) struct lhash_st_##type
static int do_cmd()
{
	
}


int main(int argc, char **argv)
{
	t_function f, *fp;
	const char *fname;
	int ret = 0;


	ret = (argc == 0) || do_cmd(prog, argc, argv);
	return (wfunc(argc, argv, &cmd));
}
