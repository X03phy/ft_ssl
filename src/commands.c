#include "ft_ssl.h"

t_cmd g_cmds[] = {
	{"md5", md5_wrapper},
	{"sha256", sha256_wrapper},
	{"whirlpool", whirlpool_wrapper},
	{NULL, NULL},
};
