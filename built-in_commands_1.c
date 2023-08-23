#include "shell.h"

int (*get_builtin(char *cmd))(char **args, char **f)
{
	builtin_t funcs[] = {{"exit",     hsh_exit},
	                     {"env",      hsh_env},
	                     {"setenv",   hsh_setenv},
	                     {"unsetenv", hsh_unsetenv},
	                     {"cd",       hsh_cd},
	                     {"alias",    hsh_alias},
	                     {"hlp",      hsh_hlp},
	                     {NULL, NULL}};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (_strcmp(funcs[i].name, cmd) == 0)
			break;
	}
	return (funcs[i].f);
}

int hsh_exit(char **args, char **f)
{
	int i = 0, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (args[0])
	{
		if (args[0][0] == '+')
		{
			i = 1;
			len_of_int++;
		}
		for (; args[0][i]; i++)
		{
			if (i <= len_of_int && args[0][i] >= '0' && args[0][i] <= '9')
				num = (num * 10) + (args[0][i] - '0');
			else
				return (create_err(--args, 2));
		}
	} else
		return (-3);
	if (num > max - 1)
		return (create_err(--args, 2));
	args -= 1;
	free_args(args, f);
	free_env();
	free_alias_list(aliases);
	exit(num);
}

int hsh_env(char **args, char __attribute__((__unused__)) **f)
{
	int idx;
	char nc = '\n';

	if (!environ)
		return (-1);
	for (idx = 0; environ[idx]; idx++)
	{
		write(STDOUT_FILENO, environ[idx], _strlen(environ[idx]));
		write(STDOUT_FILENO, &nc, 1);
	}
	(void) args;
	return (0);
}

int hsh_setenv(char **args, char __attribute__((__unused__)) **f)
{
	char **env_var = NULL, **new_environ, *new_val;
	size_t size;
	int idx;

	if (!args[0] || !args[1])
		return (create_err(args, -1));
	new_val = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_val)
		return (create_err(args, -1));
	_strcpy(new_val, args[0]);
	_strcat(new_val, "=");
	_strcat(new_val, args[1]);
	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_val;
		return (0);
	}
	for (size = 0; environ[size]; size++);
	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_val);
		return (create_err(args, -1));
	}
	for (idx = 0; environ[idx]; idx++)
		new_environ[idx] = environ[idx];
	free(environ);
	environ = new_environ;
	environ[idx] = new_val;
	environ[idx + 1] = NULL;
	return (0);
}

int hsh_unsetenv(char **args, char __attribute__((__unused__)) **f)
{
	char **env_var, **new_environ;
	size_t size;
	int idx, idx2;

	if (!args[0])
		return (create_err(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);
	for (size = 0; environ[size]; size++);
	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (create_err(args, -1));
	for (idx = 0, idx2 = 0; environ[idx]; idx++)
	{
		if (*env_var == environ[idx])
		{
			free(*env_var);
			continue;
		}
		new_environ[idx2] = environ[idx];
		idx2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;
	return (0);
}
