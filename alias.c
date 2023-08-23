#include "shell.h"

/**
 * add_alias_end - adds an alias node to the end of an alias linked list
 * @h: a pointer to the head of the alias linked list
 * @name: the name of the alias
 * @val: the value of the alias
 */
alias_t *add_alias_end(alias_t **h, char *name, char *val)
{
	alias_t *new_node = malloc(sizeof(alias_t));
	alias_t *last;

	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->val = val;
	_strcpy(new_node->name, name);
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

/**
 * free_alias_list - frees the memory allocated for an alias linked list
 * @h: a pointer to the head of the alias linked list
 */
void free_alias_list(alias_t *h)
{
	alias_t *next;

	while (h)
	{
		next = h->next;
		free(h->name);
		free(h->val);
		free(h);
		h = next;
	}
}
