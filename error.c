#include "shell.h"

/**
 * put_t - print input
 * @ss: the string
 * Return: nothing
 */

void put_t(char *ss)
{
	int i = 0;

	if (!ss)
		return;
	while (ss[i] != '\0')
	{
		put_ch(ss[i]);
		i++;
	}
}

/**
 * put_ch - write character
 * @s: the character
 * Return: 1 if true
 */

int put_ch(char s)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (s == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (s != BUF_FLUSH)
		buf[j++] = s;
	return (1);
}

/**
 * put_fd - write char with fd
 * @s: the string
 * @fd: the fild
 * Return: i if true
 */

int put_fd(char s, int fd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (s == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (s != BUF_FLUSH)
		buf[j++] = s;
	return (1);
}

/**
 * put_str - print string
 * @ss: the string
 * @fd: the filed
 * Return: the num of char
 */

int put_str(char *ss, int fd)
{
	int j = 0;

	if (!ss)
	{
		return (0);
		while (*ss)
		{
			j += put_fd(*ss++, fd);
		}
		return (j);
	}
}
