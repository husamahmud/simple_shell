#include "shell.h"

/**
 * hsh_cd - change the current working directory.
 * @args: an array of strings representing the arguments passed to the command.
 * @f: an array of strings representing the environment variables.
 * Return: 0 on success, or -1 on failure.
 */
int hsh_cd(char **args, char __attribute__((__unused__)) **f)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);
	if (args[0])
	{
		if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
		{
			if ((args[0][1] == '-' && args[0][2] == '\0') || args[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			} else
			{
				free(oldpwd);
				return (create_err(args, 2));
			}
		} else
		{
			if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode) &&
			    ((dir.st_mode & S_IXUSR) != 0))
				chdir(args[0]);
			else
			{
				free(oldpwd);
				return (create_err(args, 2));
			}
		}
	} else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}
	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);
	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);
	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (hsh_setenv(dir_info, dir_info) == -1)
		return (-1);
	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (hsh_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (args[0] && args[0][0] == '-' && args[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * print_alias - print an alias
 * @alias: A pointer to the `alias_t` structure representing the alias to be printed
 */
void print_alias(alias_t *alias)
{
	char *alias_string;
	int len = _strlen(alias->name) + _strlen(alias->val) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->val);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}

void set_alias(char *var_name, char *val)
{
	alias_t *temp = aliases;
	int len, j, k;
	char *new_val;

	*val = '\0';
	val++;
	len = _strlen(val) - _strspn(val, "'\"");
	new_val = malloc(sizeof(char) * (len + 1));
	if (!new_val)
		return;
	for (j = 0, k = 0; val[j]; j++)
	{
		if (val[j] != '\'' && val[j] != '"')
			new_val[k++] = val[j];
	}
	new_val[k] = '\0';
	while (temp)
	{
		if (_strcmp(var_name, temp->name) == 0)
		{
			free(temp->val);
			temp->val = new_val;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_alias_end(&aliases, var_name, new_val);
}

int hsh_alias(char **args, char __attribute__((__unused__)) **f)
{
	alias_t *temp = aliases;
	int i, ret = 0;
	char *val;

	if (!args[0])
	{
		while (temp)
		{
			print_alias(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		val = _strchr(args[i], '=');
		if (!val)
		{
			while (temp)
			{
				if (_strcmp(args[i], temp->name) == 0)
				{
					print_alias(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = create_err(args + i, 1);
		} else
			set_alias(args[i], val);
	}
	return (ret);
}

int hsh_hlp(char **args, char __attribute__((__unused__)) **f)
{
	if (!args[0])
		hlp_all();
	else if (_strcmp(args[0], "alias") == 0)
		hlp_alias();
	else if (_strcmp(args[0], "cd") == 0)
		hlp_cd();
	else if (_strcmp(args[0], "exit") == 0)
		hlp_exit();
	else if (_strcmp(args[0], "env") == 0)
		hlp_env();
	else if (_strcmp(args[0], "setenv") == 0)
		hlp_setenv();
	else if (_strcmp(args[0], "unsetenv") == 0)
		hlp_unsetenv();
	else if (_strcmp(args[0], "hlp") == 0)
		hlp_hlp();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}
