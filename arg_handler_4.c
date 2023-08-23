#include "shell.h"

/**
 * free_args - free command arguments and function names
 * @args: an array of strings representing the command arguments
 * @f: an array of strings representing function names or aliases
 */
void free_args(char **args, char **f)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);
	free(f);
}

/**
 * repl_aliases - replace command arguments with alias values
 * @args: an array of strings representing the command arguments
 * Return: the modified array of arguments with alias values replaced
 * If memory allocation fails, NULL is returned.
 */
char **repl_aliases(char **args)
{
	alias_t *temp;
	int i;
	char *new_val;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		while (temp)
		{
			if (_strcmp(args[i], temp->name) == 0)
			{
				new_val = malloc(sizeof(char) * (_strlen(temp->val) + 1));
				if (!new_val)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_val, temp->val);
				free(args[i]);
				args[i] = new_val;
				i--;
				break;
			}
			temp = temp->next;
		}
	}
	return (args);
}
