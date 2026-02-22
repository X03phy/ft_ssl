#include "utils/list.h"
#include <stddef.h> // NULL


t_list *list_last(t_list *list)
{
	if (!list)
		return (NULL);

	while (list->next)
		list = list->next;

	return (list);
}
