#include "ft_ssl.h"

int get_input_fd( int fd, char **lineptr, size_t *n )
{
	*n = 0;

	*lineptr = ft_calloc( 1, sizeof(char) );
	if ( !*lineptr )
		return ( 0 );

	int  r;
	char buf[43];
	char *tmp;

	while ( 1 )
	{
		r = read( fd, buf, 42 );
		if ( r == -1 ) {
			free( *lineptr );
			return ( 0 );
		}

		if ( r == 0 )
			break ;

		*n += r;
		buf[r] = '\0';

		tmp = *lineptr;
		*lineptr = ft_strjoin( *lineptr, buf );
		free( tmp );
		if ( !*lineptr )
			return ( 0 );
	}

	return ( 1 );
}
