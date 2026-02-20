#pragma once

/*
 * Structures
*/

typedef struct s_list {
	void          *data;
	struct s_list *next;
} t_list;


/*
 * prototypes
*/

t_list *list_last(t_list *list);
void list_push_back(t_list **list, t_list *new);
t_list *list_new(void *data);
