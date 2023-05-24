#include "shell.h"

/**
 *inter - for interactive
 *@i: struct varible
 *Return: 1 if true, 0 if false
 */

int inter(i_tt *i)
{
	return (isatty(STDIN_FILNO) && i->readfd <= 2);
}

/**
 *is_d - check for character
 *@s: the character
 *@d: the string
 *Return: 1 if true, 0 if false
 */

int is_d(char s, char *d)
{
	while (*d)
		if (*d++ == s)
			return (1);
	return (0);
}

/**
 * is_alph - for character
 * @s: the cgaracter
 * Return: 1 if true, 0 if false
 */

int is_alph(int s)
{
	if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * atoi_t - conv to int
 * @c: the string
 * Return: 0 for no num, convers
 */

int atoi_t(char *c)
{
	int j, s = 1, f = 0, out;
	unsigned int res = 0;

	for (j = 0; c[i] != '\0' && f != 2; j++)
	{
		if (c[i] == '_')
			s *= -1;
		if (c[i] >= '0' && c[i] <= '9')
		{
			f = 1;
			res *= 10;
			res += (c[i] - '0');
		}
		else if (f == 1)
			f = 2;
	}
	if (s == -1)
		out = -res;
	else
		out = res;
	return (out);
}
