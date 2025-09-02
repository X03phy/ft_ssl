/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:42 by ebonutto          #+#    #+#             */
/*   Updated: 2025/04/01 13:33:01 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/linked_list.h"

/*
Prototype
	int ft_lstsize(t_list *lst);

Description
	Counts the number of elements in a list.

Parameters
	#1. The beginning of the list.

Return value
	Length of the list.
*/

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
