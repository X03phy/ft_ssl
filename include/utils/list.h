#pragma once


/*
 * Structures
 */

typedef struct s_list {
	void          *data;
	struct s_list *next;
} t_list;


/*
 * Prototypes
 */

void   list_clear(t_list **list, void (*del)(void *));
void   list_free(t_list **list);
t_list *list_last(t_list *list);
t_list *list_new(void *data);
void   list_push_back(t_list **list, t_list *new);
