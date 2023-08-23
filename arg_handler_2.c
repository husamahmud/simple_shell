#include "shell.h"

/**
 * num_len - calculates the length of an integer
 * @num: the integer to calculate the length for
 * Return: the length of the integer
 */
int num_len(int num)
{
	unsigned int num1;
	int len = 1;

	if (num < 0)
	{
		len++;
		num1 = num * -1;
	} else
		num1 = num;
	while (num1 > 9)
	{
		len++;
		num1 /= 10;
	}
	return (len);
}

/**
 * _itos - converts an integer to a string representation
 * @num: the integer to convert to a string
 * Return: a dynamically allocated string representing the integer
 * or NULL if memory allocation fails
 */
char *_itos(int num)
{
	char *buf;
	int len = num_len(num);
	unsigned int num1;

	buf = malloc(sizeof(char) * (len + 1));
	if (!buf)
		return (NULL);
	buf[len] = '\0';
	if (num < 0)
	{
		num1 = num * -1;
		buf[0] = '-';
	} else
		num1 = num;
	len--;
	do
	{
		buf[len] = (num1 % 10) + '0';
		num1 /= 10;
		len--;
	} while (num1 > 0);
	return (buf);
}

/**
 * get_env_val - retrieves the value of an environment variable
 * @beg: a pointer to the beginning of the environment variable name
 * @len: the length of the environment variable name
 */
char *get_env_val(char *beg, int len)
{
	char **var_addr;
	char *repl = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beg, len);
	var_addr = _getenv(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		repl = malloc(_strlen(temp) + 1);
		if (repl)
			_strcpy(repl, temp);
	}
	return (repl);
}

/**
 * get_pid - retrieves the process ID of the current process
 * Return: a dynamically allocated string representing the process ID
 * or NULL if the PID cannot be retrieved or if memory allocation fails
 */
char *get_pid(void)
{
	size_t i = 0;
	char *buf;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buf = malloc(120);
	if (!buf)
	{
		close(file);
		return (NULL);
	}
	read(file, buf, 120);
	while (buf[i] != ' ')
		i++;
	buf[i] = '\0';
	close(file);
	return (buf);
}

/**
 * var_repl - variable replacement in a string
 * @line: a pointer to the string to perform variable replacement on
 * @exe_ret: a pointer to an integer representing the return value
 * of a previous execution
 */
void var_repl(char **line, const int *exe_ret)
{
	int j, k = 0, len;
	char *repl = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] && old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				repl = get_pid();
				k = j + 2;
			} else if (old_line[j + 1] == '?')
			{
				repl = _itos(*exe_ret);
				k = j + 2;
			} else if (old_line[j + 1])
			{
				for (k = j + 1;
				     old_line[k] && old_line[k] != '$' && old_line[k] != ' '; k++);
				len = k - (j + 1);
				repl = get_env_val(&old_line[j + 1], len);
			}
			new_line = malloc(j + _strlen(repl) + _strlen(&old_line[k]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, j);
			if (repl)
			{
				_strcat(new_line, repl);
				free(repl);
				repl = NULL;
			}
			_strcat(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			j = -1;
		}
	}
}


