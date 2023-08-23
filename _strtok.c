#include "shell.h"

/**
 * token_len - calculates the length of a token in a string based on a delimiter
 * @str: a pointer to the string to analyze
 * @delim: a pointer to the delimiter character
 * Return: the length of the token
 */
int token_len(const char *str, const char *delim)
{
	int idx = 0, len = 0;

	while (*(str + idx) && *(str + idx) != *delim)
		len++, idx++;
	return (len);
}

/**
 * count_tokens - counts the number of tokens in a string based on a delimiter
 * @str: a pointer to the string to analyze
 * @delim: a pointer to the delimiter string
 */
int count_tokens(char *str, char *delim)
{
	int idx, tokens = 0, len = 0;

	for (idx = 0; *(str + idx); idx++)
		len++;
	for (idx = 0; idx < len; idx++)
	{
		if (*(str + idx) != *delim)
		{
			tokens++;
			idx += token_len(str + idx, delim);
		}
	}
	return (tokens);
}

/**
 * _strtok - tokenizes a string into multiple substrings based on a delimiter
 * @line: a pointer to the string to tokenize
 * @delim: a pointer to the delimiter string
 * Return: array of pointers to tokenized substrings
 * or NULL if an error occurs
 */
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int idx = 0, tokens, t, letters, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);
	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);
	for (t = 0; t < tokens; t++)
	{
		while (line[idx] == *delim)
			idx++;
		letters = token_len(line + idx, delim);
		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (idx -= 1; idx >= 0; idx--)
				free(ptr[idx]);
			free(ptr);
			return (NULL);
		}
		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = line[idx];
			idx++;
		}
		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;
	return (ptr);
}
