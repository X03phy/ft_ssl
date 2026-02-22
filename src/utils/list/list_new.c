#include "utils/list.h"
#include <stdlib.h> // malloc(), NULL


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
