#include "ft_ssl.h"

/* For ft_strcasecmp() */
#include "string.h"


t_ssl_wfunc parse_cmd( t_ssl_cmd *cmd, char *arg )
{
	for ( int i = 0; g_cmds[i].name; ++i )
	{
		if ( ft_strcasecmp( g_cmds[i].name, arg ) == 0 )
		{
			cmd->name = g_cmds[i].name;
			cmd->type = g_cmds[i].type;
			if ( g_cmds[i].type == CMD_HASH )
			{
				cmd->hash.hash_size =  g_cmds[i].hash.hash_size;
				cmd->hash.hash_func =  g_cmds[i].hash.hash_func;
				return ( hash_wrapper );
			}
			else
			{
				cmd->cipher.key_size =  g_cmds[i].cipher.key_size;
				cmd->cipher.encrypt_func =  g_cmds[i].cipher.encrypt_func;
				cmd->cipher.decrypt_func =  g_cmds[i].cipher.decrypt_func;
				return ( hash_wrapper );
			}
		}
	}
	return ( NULL );
}
