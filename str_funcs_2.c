#include "shell.h"

/**
 * _strchr - find the first occurrence of a character in a string
 * @s: The string to search in
 * @c: The character to find
 * Return: a pointer to the first occurrence of char in string
 * or NULL if 'c' is not found
 */
char *_strchr(char *s, char c)
{
	int idx;

	for (idx = 0; s[idx]; idx++)
		if (s[idx] == c)
			return (s + idx);
	return (NULL);
}

/**
 * _strspn - get the length of the initial segment of a string that contains only
 * characters from another string
 * @s: the string to examine
 * @accept: the string containing the characters to be matched
 * Return: the length of the initial segment of 's' that consists
 * only of characters from 'accept'
 */
int _strspn(char *s, char *accept)
{
	int bytes = 0;
	int idx;

	while (*s)
	{
		for (idx = 0; accept[idx]; idx++)
		{
			if (*s == accept[idx])
			{
				bytes++;
				break;
			}
		}
		s++;
	}
	return (bytes);
}

/**
 * _strcmp - compare two strings
 * @s1: the first string
 * @s2: the second string
 * Return: an integer less than, equal to, or greater than zero if 's1' is found
 * to be less than, equal to, or greater than 's2', respectively
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
		s1++, s2++;
	if (*s1 != *s2)
		return (*s1 - *s2);
	return (0);
}

/**
 * Compare two strings up to a specified length.
 * @s1: the first string
 * @s2: the second string
 * @n: the maximum number of characters to compare
 * Return: An integer less than, equal to, or greater than zero if the first 'n'
 * characters of 's1' are found to be less than, equal to, or greater than the
 * first 'n' characters of 's2', respectively
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}
