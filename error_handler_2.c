#include "shell.h"

char *err_2_syntax(char **args)
{
	char *err, *hist_str;
	int len;

	hist_str = _itos(hist);
	if (!hist_str)
		return (NULL);
	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 33;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(hist_str);
		return (NULL);
	}
	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_str);
	_strcat(err, ": Syntax err: \"");
	_strcat(err, args[0]);
	_strcat(err, "\" unexpected\n");
	free(hist_str);
	return (err);
}

char *err_126(char **args)
{
	char *err, *hist_str;
	int len;

	hist_str = _itos(hist);
	if (!hist_str)
		return (NULL);
	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(hist_str);
		return (NULL);
	}
	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_str);
	_strcat(err, ": ");
	_strcat(err, args[0]);
	_strcat(err, ": Permission denied\n");
	free(hist_str);
	return (err);
}

char *err_127(char **args)
{
	char *err, *hist_str;
	int len;

	hist_str = _itos(hist);
	if (!hist_str)
		return (NULL);
	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 16;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(hist_str);
		return (NULL);
	}
	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_str);
	_strcat(err, ": ");
	_strcat(err, args[0]);
	_strcat(err, ": not found\n");
	free(hist_str);
	return (err);
}
