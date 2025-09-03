/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 08:56:21 by ebonutto          #+#    #+#             */
/*   Updated: 2025/09/01 15:42:13 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int ft_final_save( char **lineptr, char *buf, int *n, size_t pos )
{
	char end[pos + 1];
	char *tmp;

	*n += pos;

	ft_strlcpy( end, buf, pos + 1);

	tmp = *lineptr;
	*lineptr = ft_strjoin( *lineptr, end );
	free( tmp );
	if ( !*lineptr )
		return ( 0 );

	ft_strlcpy( buf, buf + pos, BUFSIZ - pos + 1 );

	return ( 1 );
}

static int ft_read_save( char **lineptr, char *buf, int *n, int fd )
{
	char    *tmp;
	ssize_t r;

	while ( ( r = read( fd, buf, BUFSIZ ) ) > 0 )
	{
		buf[r] = '\0';

		tmp = ft_strchr( buf, '\n' );
		if ( tmp )
			return ( ft_final_save( lineptr, buf, n, tmp - buf + 1 ) );

		*n += r;
		tmp = *lineptr;
		*lineptr = ft_strjoin( *lineptr, buf );
		free( tmp );
		if ( !*lineptr )
			return ( 0 );
	}

	if ( r == -1 ) {
		free( *lineptr );
		*lineptr = NULL;
		return ( 0 );
	}

	return ( 1 );
}

ssize_t get_next_line( char **lineptr, int *n, int fd )
{
	static char	buf[BUFSIZ + 1];

	if ( !lineptr || !n || fd < 0 || BUFSIZ <= 0 )
		return ( -1 );

	*n = 0;

	*lineptr = ft_calloc( 1, sizeof(char) );
	if ( !*lineptr )
		return ( -1 );

	if ( !ft_read_save( lineptr, buf, n, fd ) )
		return ( -1 );

	if ( (*lineptr)[0] == '\0' ) {
		free( *lineptr );
		*lineptr = NULL;
		return ( 0 );
	}

	return ( *n );
}
