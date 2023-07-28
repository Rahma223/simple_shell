#include "shell.h"

/**
 * _ep - print
 * @s: the str
 *
 * Return: Nothing
 */
void _ep(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_epc(s[i]);
		i++;
	}
}

/**
 * _epc - the writes
 * @ca: The char
 *
 * Return: On succ
 */
int _epc(char ca)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ca == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (ca != BUF_FLUSH)
		buf[i++] = ca;
	return (1);
}

/**
 * _puf - the writ
 * @ca: The chara
 * @f: The filed
 *
 * Return: On succes
 */
int _puf(char ca, int f)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ca == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(f, buf, i);
		i = 0;
	}
	if (ca != BUF_FLUSH)
		buf[i++] = ca;
	return (1);
}

/**
 * _pus - the pr
 * @s: the st
 * @f: the filed
 *
 * Return: the numb
 */
int _pus(char *s, int f)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s)
	{
		i += _puf(*s++, f);
	}
	return (i);
}
