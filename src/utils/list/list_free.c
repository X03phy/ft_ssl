#include "utils/list.h"
#include <stdlib.h> // free(), NULL


void list_free(t_list **list)
{
	t_list *tmp;

	if (!list)
		return ;

	while (*list) {
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
}
