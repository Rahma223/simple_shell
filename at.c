#include "shell.h"

/**
 * inter - returns true
 * @in: a struct
 *
 * Return: 1 if inter
 */
int inter(info_t *in)
{
	return (isatty(STDIN_FILENO) && in->readfd <= 2);
}

/**
 * is_de - a checks
 * @ca: the char to
 * @de: the de
 * Return: 1 if tr
 */
int is_de(char ca, char *de)
{
	while (*de)
		if (*de++ == ca)
			return (1);
	return (0);
}

/**
 * isalp - checks to
 * @ca: The char
 * Return: 1 if c is alph
 */

int isalp(int ca)
{
	if ((ca >= 'a' && ca <= 'z') || (ca >= 'A' && ca <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _at - converts a str
 * @sa: the string
 * Return: 0 if no numbers
 */

int _at(char *sa)
{
	int i, si = 1, f = 0, o;
	unsigned int res = 0;

	for (i = 0; sa[i] != '\0' && f != 2; i++)
	{
		if (sa[i] == '-')
			si *= -1;

		if (sa[i] >= '0' && sa[i] <= '9')
		{
			f = 1;
			res *= 10;
			res += (sa[i] - '0');
		}
		else if (f == 1)
			f = 2;
	}

	if (si == -1)
		o = -res;
	else
		o = res;

	return (o);
}
