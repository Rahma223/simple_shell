#include "shell.h"

/**
 * err_t - conv string
 * @c: the string
 * Return: 0 if on number
 */

int err_t(char *c)
{
	int j = 0;
	unsigned long int res = 0;

	if (*c == '+')
		c++;
	for (j = 0;  c[j] != '\0'; j++)
	{
		if (c[j] >= '0' && c[j] <= '9')
		{
			res *= 10;
			res += (c[j] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_e - print an error
 * @i: struct var
 * @ss: the string
 * Return: 0 if no number
 */

void print_e(i_tt *i, char *ss)
{
	put_t(i->fname);
	put_t(": ");
	print_dd(i->line_count, STDERR_FILENO);
	put_t(": ");
	put_t(i->argv[0]);
	put_t(": ");
	put_t(ss);
}

/**
 * print_dd - print integer
 * @in: the input
 * @fd: the filed
 * Return: number of char
 */

int print_dd(int in, int fd)
{

	int (*__putchar)(char) = _putchar;
	int j, con = 0;
	unsigned int _abs_, cur;

	if (fd == STDERR_FILENO)
		__putchar = put_ch;
	if (in < 0)
	{
		_abs_ = -in;
		__putchar('-');
		con++;
	}
	else
		_abs_ = in;
	cur = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + cur / j);
			con++;
		}
		cur %= j;
	}
	__putchar('0' + cur);
	con++;

	return (con);
}

/**
 * conv_num - coverter fun
 * @num: number
 * @bas: base
 * @f: arg flag
 * Return: string
 */

char *conv_num(long int num, int bas, int f)
{
	static char *arr;
	static char buffer[50];
	char s = 0;
	char *p;
	unsigned long n = num;

	if (!(f & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		s = '-';

	}
	arr = f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buffer[49];
	*p = '\0';

	do	{
		*--p = arr[n % bas];
		n /= bas;
	} while (n != 0);

	if (s)
		*--p = s;
	return (p);
}

/**
 * rem_c - function replace#
 * @b: adderss string
 * Return: 0
 */

void rem_c(char *b)
{
	int j;

	for (j = 0; b[j] != '\0'; j++)
		if (b[j] == '#' && (!j || b[j - 1] == ' '))
		{
			b[j] = '\0';
			break;
		}
}
