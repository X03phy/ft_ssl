#include "utils/list.h"


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
