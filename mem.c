#include "shell.h"

/**
 * bfree - frees a poin
 * @p: addresree
 *
 * Return: 1 if
 */
int bfree(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
		return (1);
	}
	return (0);
}
