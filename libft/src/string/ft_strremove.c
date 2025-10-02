#include "string.h"

char *ft_strremove( const char *str, const char c )
{
	size_t len;
	size_t i, j;
	char   *s;

	if ( !str || c == '\0' ) // Handle that case for a clean function
		return ( NULL );

	len = 0;
	i = 0;
	while ( str[i] )
	{
		if ( str[i] != c )
			len += 1;
		i += 1;
	}

	s = malloc( sizeof(char) * len + 1 );
	if ( !s )
		return ( NULL );

	i = 0;
	j = 0;
	while ( str[i] )
	{
		if ( str[i] != c )
		{
			s[j] = str[i];
			j += 1;
		}
		i += 1;
	}
	s[j] = '\0';

	return ( s );
}
