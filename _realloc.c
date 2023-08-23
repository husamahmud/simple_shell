#include "shell.h"

/**
 * _realloc - reallocates memory for a block of memory with a new size
 * @ptr: A pointer to the original memory block
 * @old_size: The old size of the memory block
 * @new_size: The new size to allocate
 * Return: a pointer to the newly allocated memory block
 * or NULL if an error occurred
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *mem;
	char *ptr_copy, *filler;
	unsigned int idx;

	if (new_size == old_size)
		return (ptr);
	if (ptr == NULL)
	{
		mem = malloc(new_size);
		if (mem == NULL)
			return (NULL);
		return (mem);
	}
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	ptr_copy = ptr;
	mem = malloc(sizeof(*ptr_copy) * new_size);
	if (mem == NULL)
	{
		free(ptr);
		return (NULL);
	}
	filler = mem;
	for (idx = 0; idx < old_size && idx < new_size; idx++)
		filler[idx] = *ptr_copy++;
	free(ptr);
	return (mem);
}
