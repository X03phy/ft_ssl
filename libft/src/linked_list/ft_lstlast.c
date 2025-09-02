/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:35 by ebonutto          #+#    #+#             */
/*   Updated: 2025/04/01 13:33:01 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/linked_list.h"

/*
Prototype
	t_list *ft_lstlast(t_list *lst);

Description
	Returns the last element of the list.

Parameters
	#1. The beginning of the list.

Return value
	Last element of the list.
*/

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
