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
				cmd->encoding.encode_func =  g_cmds[i].encoding.encode_func;
				cmd->encoding.decode_func =  g_cmds[i].encoding.decode_func;
				return ( encoding_wrapper );
			}
		}
	}
	return ( NULL );
}
