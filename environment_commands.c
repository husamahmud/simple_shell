#include "shell.h"

/**
 * _copyenv - Copy the environment variables.
 * Return: an array of strings representing the copied environment variables
 * If memory allocation fails, NULL is returned
 */
char **_copyenv(void)
{
	char **new_environ;
	size_t size;
	int idx;

	for (size = 0; environ[size]; size++);
	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);
	for (idx = 0; environ[idx]; idx++)
	{
		new_environ[idx] = malloc(_strlen(environ[idx]) + 1);
		if (!new_environ[idx])
		{
			for (idx--; idx >= 0; idx--)
				free(new_environ[idx]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[idx], environ[idx]);
	}
	new_environ[idx] = NULL;
	return (new_environ);
}

/**
 * free_env - free the environment variables
 */
void free_env(void)
{
	int idx;

	for (idx = 0; environ[idx]; idx++)
		free(environ[idx]);
	free(environ);
}

/**
 * _getenv - get the value of an environment variable
 * @var: the name of the environment variable to retrieve
 * Return: a pointer to the environment variable if found, or NULL if not found
 */
char **_getenv(const char *var)
{
	int idx, len;

	len = _strlen(var);
	for (idx = 0; environ[idx]; idx++)
		if (_strncmp(var, environ[idx], len) == 0)
			return (&environ[idx]);
	return (NULL);
}
