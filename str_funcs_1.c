#include "shell.h"


size_t _strlen(const char *s)
{
	size_t len = 0;

	while (s[len])
		len++;
	return (len);
}

char *_strcat(char *dest, const char *src)
{
	char *dest_temp;
	const char *src_temp;

	dest_temp = dest;
	src_temp = src;
	while (*dest_temp != '\0')
		dest_temp++;
	while (*src_temp != '\0')
		*dest_temp++ = *src_temp++;
	*dest_temp = '\0';
	return (dest);
}

char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';
	return (dest);
}

char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
