#include "shell.h"

char *get_loc(char *cmd)
{
	char **path, *temp;
	list_t *dirs, *h;
	struct stat st;

	path = _getenv("PATH");
	if (!path || !(*path))
		return (NULL);
	dirs = get_path_dir(*path + 5);
	h = dirs;
	while (dirs)
	{
		temp = malloc(_strlen(dirs->dir) + _strlen(cmd) + 2);
		if (!temp)
			return (NULL);
		_strcpy(temp, dirs->dir);
		_strcat(temp, "/");
		_strcat(temp, cmd);
		if (stat(temp, &st) == 0)
		{
			free_list(h);
			return (temp);
		}
		dirs = dirs->next;
		free(temp);
	}
	free_list(h);
	return (NULL);
}

char *fill_path_dir(char *path)
{
	int i, length = 0;
	char *path_copy, *pwd;

	pwd = *(_getenv("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				length += _strlen(pwd) + 1;
			else
				length++;
		} else
			length++;
	}
	path_copy = malloc(sizeof(char) * (length + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				_strcat(path_copy, pwd);
				_strcat(path_copy, ":");
			} else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				_strcat(path_copy, ":");
				_strcat(path_copy, pwd);
			} else
				_strcat(path_copy, ":");
		} else
			_strncat(path_copy, &path[i], 1);
	}
	return (path_copy);
}

list_t *get_path_dir(char *path)
{
	int idx;
	char **dirs, *path_copy;
	list_t *h = NULL;

	path_copy = fill_path_dir(path);
	if (!path_copy)
		return (NULL);
	dirs = _strtok(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);
	for (idx = 0; dirs[idx]; idx++)
	{
		if (add_node_end(&h, dirs[idx]) == NULL)
		{
			free_list(h);
			free(dirs);
			return (NULL);
		}
	}
	free(dirs);
	return (h);
}

int exec(char **args, char **f)
{
	pid_t child_pid;
	int status, flag = 0, ret = 0;
	char *cmd = args[0];

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		flag = 1;
		cmd = get_loc(cmd);
	}
	if (!cmd || (access(cmd, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (create_err(args, 126));
		else
			ret = (create_err(args, 127));
	} else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(cmd);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(cmd, args, environ);
			if (errno == EACCES)
				ret = (create_err(args, 126));
			free_env();
			free_args(args, f);
			free_alias_list(aliases);
			_exit(ret);
		} else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(cmd);
	return (ret);
}

