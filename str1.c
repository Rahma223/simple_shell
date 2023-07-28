#include "shell.h"

/**
 * _st - copie
 * @de: the desti
 * @sr: th
 *
 * Return: pointe
 */
char *_st(char *de, char *sr)
{
	int i = 0;

	if (de == sr || sr == 0)
		return (de);
	while (sr[i])
	{
		de[i] = sr[i];
		i++;
	}
	de[i] = 0;
	return (de);
}

/**
 * _strdu - duplicat
 * @st: the strin
 *
 * Return: pointer
 */
char *_strdu(const char *st)
{
	int len = 0;
	char *re;

	if (st == NULL)
		return (NULL);
	while (*st++)
		len++;
	re = malloc(sizeof(char) * (len + 1));
	if (!re)
		return (NULL);
	for (len++; len--;)
		re[len] = *--st;
	return (re);
}

/**
 * _pu - prints an
 * @st: the s
 * Return: No
 */
void _pu(char *st)
{
	int i = 0;

	if (!st)
		return;
	while (st[i] != '\0')
	{
		_puc(str[i]);
		i++;
	}
}

/**
 * _puc - write
 * @ca: The character
 *
 * Return: On succes
 */
int _puc(char ca)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ca == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (ca != BUF_FLUSH)
		buf[i++] = ca;
	return (1);
}
