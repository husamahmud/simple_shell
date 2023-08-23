#include "shell.h"

/**
 * get_args - read and process user input from the standard input
 * @line: a pointer to a character buffer to store the user input
 * @exe_ret: a pointer to an integer representing the return value
 * of a previous execution
 * Return A dynamically allocated string representing the processed user input
 * or NULL if an error occurs or if the end of input is reached
 */
char *get_args(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prmpt = "$ ";

	if (line)
		free(line);
	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prmpt, 2);
		return (get_args(line, exe_ret));
	}
	line[read - 1] = '\0';
	var_repl(&line, exe_ret);
	hdl_line(&line, read);
	return (line);
}

/**
 * call_args - call and execute command arguments
 * @args: an array of strings representing the command arguments
 * @f: an array of strings representing function names or aliases
 * @exe_ret: a pointer to an integer representing the return value
 * of a previous execution
 * Return: the return value of the executed command
 */
int call_args(char **args, char **f, int *exe_ret)
{
	int ret, idx;

	if (!args[0])
		return (*exe_ret);
	for (idx = 0; args[idx]; idx++)
	{
		if (_strncmp(args[idx], "||", 2) == 0)
		{
			free(args[idx]);
			args[idx] = NULL;
			args = repl_aliases(args);
			ret = run_args(args, f, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++idx];
				idx = 0;
			} else
			{
				for (idx++; args[idx]; idx++)
					free(args[idx]);
				return (ret);
			}
		} else if (_strncmp(args[idx], "&&", 2) == 0)
		{
			free(args[idx]);
			args[idx] = NULL;
			args = repl_aliases(args);
			ret = run_args(args, f, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++idx];
				idx = 0;
			} else
			{
				for (idx++; args[idx]; idx++)
					free(args[idx]);
				return (ret);
			}
		}
	}
	args = repl_aliases(args);
	ret = run_args(args, f, exe_ret);
	return (ret);
}

/**
 * run_args - run command arguments
 * @args: an array of strings representing the command arguments
 * @f: an array of strings representing function names or aliases
 * @exe_ret: a pointer to an integer representing the return value
 * of a previous execution
 * Return: The return value of the executed command
 */
int run_args(char **args, char **f, int *exe_ret)
{
	int ret, i;
	int (*builtin)(char **args, char **f);

	builtin = get_builtin(args[0]);
	if (builtin)
	{
		ret = builtin(args + 1, f);
		if (ret != EXIT)
			*exe_ret = ret;
	} else
	{
		*exe_ret = exec(args, f);
		ret = *exe_ret;
	}
	hist++;
	for (i = 0; args[i]; i++)
		free(args[i]);
	return (ret);
}

/**
 * hdl_args - handle command arguments
 * @exe_ret: a pointer to an integer representing the return value
 * of a previous execution
 * Return: the return value of the executed command
 */
int hdl_args(int *exe_ret)
{
	int ret = 0, idx;
	char **args, *line = NULL, **f;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	f = args;
	for (idx = 0; args[idx]; idx++)
	{
		if (_strncmp(args[idx], ";", 1) == 0)
		{
			free(args[idx]);
			args[idx] = NULL;
			ret = call_args(args, f, exe_ret);
			args = &args[++idx];
			idx = 0;
		}
	}
	if (args)
		ret = call_args(args, f, exe_ret);
	free(f);
	return (ret);
}

/**
 * check_args - check command arguments for syntax errors
 * @args: an array of strings representing the command arguments
 * Return: 0 if the arguments are valid, otherwise an error code
 */
int check_args(char **args)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; args[i]; i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (create_err(&args[i], 2));
			nex = args[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_err(&args[i + 1], 2));
		}
	}
	return (0);
}
