/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:11 by ebonutto          #+#    #+#             */
/*   Updated: 2025/04/01 13:29:42 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/char.h"

/*
Prototype
   int ft_isprint(int c);

Description
   Checks whether the given character is a printable character
	(from the space character to ~ in the ASCII table).

Parameters
   #1. c : The character to check, passed as an `int` (typically a `char`).

Return value
   The function returns a non-zero value if the character is printable,
	and 0 if it is not.
*/

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
