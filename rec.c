#include "shell.h"

/**
 * _mem - fills memory
 * @sa: the pointe
 * @ba: tht par
 * @na: the amou
 * Return: (s) a pointer
 */
char *_mem(char *sa, char ba, unsigned int na)
{
	unsigned int i;

	for (i = 0; i < na; i++)
		sa[i] = ba;
	return (sa);
}

/**
 * ffree - frees
 * @p: strin
 */
void ffree(char **p)
{
	char **aa = p;

	if (!p)
		return;
	while (*p)
		free(*p++);
	free(aa);
}

/**
 * _re - reas
 * @pt: pointer
 * @o_size: byte size
 * @n_size: byte size
 *
 * Return: pointer to
 */
void *_re(void *pt, unsigned int o_size, unsigned int n_size)
{
	char *p;

	if (!pt)
		return (malloc(n_size));
	if (!n_size)
		return (free(pt), NULL);
	if (n_size == o_size)
		return (pt);

	p = malloc(n_size);
	if (!p)
		return (NULL);

	o_size = o_size < n_size ? o_size : n_size;
	while (o_size--)
		p[o_size] = ((char *)pt)[o_size];
	free(pt);
	return (p);
}
