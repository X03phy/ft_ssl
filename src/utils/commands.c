#include "ft_ssl.h"
#include "md5.h"
#include "sha256.h"
#include "whirlpool.h"

t_ssl_cmd g_cmds[] = {
	{ 
		.name = "md5", 
		.type = CMD_HASH, 
		.hash = { 
			.hash_size = 16, 
			.hash_func = md5 
		} 
	},
	{ 
		.name = "sha256", 
		.type = CMD_HASH, 
		.hash = { 
			.hash_size = 32, 
			.hash_func = sha256 
		} 
	},
	{ 
		.name = "whirlpool", 
		.type = CMD_HASH, 
		.hash = { 
			.hash_size = 64, 
			.hash_func = whirlpool 
		} 
	},
	{ NULL, 0, { {0} } } // fin du tableau
};
