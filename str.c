#include "shell.h"

/**
 * _str - returns
 * @sa: the strin
 *
 * Return: intege
 */
int _str(char *sa)
{
	int i = 0;

	if (!sa)
		return (0);

	while (*sa++)
		i++;
	return (i);
}

/**
 * strc - performs lexicogarphic
 * @s1a: the first
 * @s2a: the se
 *
 * Return: negative if s1 == s2
 */
int strc(char *s1a, char *s2a)
{
	while (*s1a && *s2a)
	{
		if (*s1a != *s2a)
			return (*s1a - *s2a);
		s1a++;
		s2a++;
	}
	if (*s1a == *s2a)
		return (0);
	else
		return (*s1a < *s2a ? -1 : 1);
}

/**
 * s_w - checks if needle
 * @hay: the par
 * @ne: the substri
 *
 * Return: address of next
 */
char *s_w(const char *hay, const char *ne)
{
	while (*ne)
		if (*ne++ != *hay++)
			return (NULL);
	return ((char *)hay);
}

/**
 * _strc - concaten
 * @de: the destinati
 * @sr: the s
 *
 * Return: pointer to des
 */
char *_strc(char *de, char *sr)
{
	char *re = de;

	while (*de)
		de++;
	while (*sr)
		*de++ = *sr++;
	*de = *sr;
	return (re);
}
