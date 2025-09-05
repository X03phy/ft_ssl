#include "ft_ssl.h"

t_ssl_wfunc parse_cmd( t_ssl_cmd *cmd )
{
	for ( int i = 0; g_cmds[i].name; ++i )
	{
		if ( ft_strcmp( g_cmds[i].name, cmd->name ) == 0 )
		{
			cmd->type = CMD_HASH;
			cmd->hash.hash_size =  g_cmds[i].hash.hash_size;
			cmd->hash.hash_func =  g_cmds[i].hash.hash_func;
			return ( hash_wrapper );
		}
	}
	return ( NULL );
}
