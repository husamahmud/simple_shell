#include "shell.h"

list_t *add_node_end(list_t **h, char *dir)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *last;

	if (!new_node)
		return (NULL);
	new_node->dir = dir;
	new_node->next = NULL;
	if (*h)
	{
		last = *h;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	} else
		*h = new_node;
	return (new_node);
}

void free_list(list_t *h)
{
	list_t *next;

	while (h)
	{
		next = h->next;
		free(h->dir);
		free(h);
		h = next;
	}
}
