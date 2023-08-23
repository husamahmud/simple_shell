#include "shell.h"

/**
 * assign_lineptr - assigns a line pointer and size for a given buffer
 * @lineptr: a pointer to the line pointer variable
 * @n: a pointer to the size variable
 * @buf: the buffer to assign
 * @b: the size of the buffer
 */
void assign_lineptr(char **lineptr, size_t *n, char *buf, size_t b)
{
	if (*lineptr == NULL)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buf;
	} else if (*n < b)
	{
		if (b > 120)
			*n = b;
		else
			*n = 120;
		*lineptr = buf;
	} else
	{
		_strcpy(*lineptr, buf);
		free(buf);
	}
}

/**
 * _getline - reads a line from a stream into a dynamically allocated buffer
 * @lineptr: a pointer to the line pointer variable
 * @n: a pointer to the size variable
 * @stream: the input stream to read from
 * Return: the number of characters read or -1 if an error occurred
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static ssize_t input;
	ssize_t ret;
	char c = 'x', *buf;
	int r;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;
	buf = malloc(sizeof(char) * 120);
	if (!buf)
		return (-1);
	while (c != '\n')
	{
		r = read(STDIN_FILENO, &c, 1);
		if (r == -1 || (r == 0 && input == 0))
		{
			free(buf);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= 120)
			buf = _realloc(buf, input, input + 1);
		buf[input] = c;
		input++;
	}
	buf[input] = '\0';
	assign_lineptr(lineptr, n, buf, input);
	ret = input;
	if (r != 0)
		input = 0;
	return (ret);
}
