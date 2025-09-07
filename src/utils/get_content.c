#include "ft_ssl.h"

/* For read() */
#include <unistd.h>

/* For free() */
#include <stdlib.h>

/* For ft_calloc() */
#include "memory.h"

/* For ft_strjoin() */
#include "string.h"


int get_content_fd( int fd, char **lineptr, size_t *n )
{
	*n = 0;

	*lineptr = ft_calloc( 1, sizeof(char) );
	if ( !*lineptr )
	{
		print_internal_error( "ft_calloc()" );
		return ( 0 );
	}

	int  r;
	char buf[43];
	char *tmp;

	while ( 1 )
	{
		r = read( fd, buf, 42 );
		if ( r == -1 ) {
			print_internal_error( "read()" );
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
		{
			print_internal_error( "ft_strjoin" );
			return ( 0 );
		}
	}

	return ( 1 );
}
