/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:40 by ebonutto          #+#    #+#             */
/*   Updated: 2025/04/01 13:33:01 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/linked_list.h"

/*
Prototype
	t_list *ft_lstnew(void *content);

Description
	Allocates (with malloc(3)) and returns a new
	element. The variable ’content’ is initialized
	with the value of the parameter ’content’. The
	variable ’next’ is initialized to NULL.

Parameters
	#1. The content to create the new element with.

Return value
	The new element.
*/

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}
