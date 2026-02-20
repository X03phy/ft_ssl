#include "ft_ssl.h"
#include "md5.h"
#include "sha256.h"
#include "whirlpool.h"
#include "base64.h"

t_ssl_cmd g_cmds[] = {
	{ 
		.name = "MD5", 
		.type = CMD_HASH, 
		.hash = { 
			.hash_size = 16, 
			.hash_func = md5 
		} 
	},
	{ 
		.name = "SHA256", 
		.type = CMD_HASH, 
		.hash = { 
			.hash_size = 32, 
			.hash_func = sha256 
		} 
	},
	{ 
		.name = "WHIRLPOOL", 
		.type = CMD_HASH, 
		.hash = { 
			.hash_size = 64, 
			.hash_func = whirlpool 
		} 
	},
	{ 
		.name = "BASE64", 
		.type = CMD_ENCODING, 
		.encoding = { 
			.encode_func = base64_encode,
			.decode_func = base64_decode,
		} 
	},
	{ NULL, 0, { {0} } } // fin du tableau
};
