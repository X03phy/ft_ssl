#include "list.h"
#include <stdlib.h> // NULL, malloc(), free()


/*
 * Functions
*/

t_list *list_last(t_list *list)
{
	if (!list)
		return (NULL);

	while (list->next)
		list = list->next;

	return (list);
}


void list_push_back(t_list **list, t_list *new)
{
	if (!list || !new)
		return ;

	if (!*list) {
		*list = new;
		return ;
	}

	list_last(*list)->next = new; 
}


t_list *list_new(void *data)
{
	t_list *list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);

	list->data = data;
	list->next = NULL;

	return (list);
}
