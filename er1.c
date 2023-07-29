#include "shell.h"

/**
 * _err - the convert
 * @sa: the strin
 * Return: 0 if no num
 */
int _err(char *sa)
{
	int i = 0;
	unsigned long int res = 0;

	if (*sa == '+')
		sa++;
	for (i = 0;  sa[i] != '\0'; i++)
	{
		if (sa[i] >= '0' && sa[i] <= '9')
		{
			res *= 10;
			res += (sa[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * p_err - the print
 * @in: the para
 * @es: string con
 * Return: 0 if no num
 */
void p_err(info_t *in, char *es)
{
	_ep(in->fname);
	_ep(": ");
	p_d(in->line_count, STDERR_FILENO);
	_ep(": ");
	_ep(in->argv[0]);
	_ep(": ");
	_ep(es);
}

/**
 * p_d - function pri
 * @in: a in
 * @f: the fi
 *
 * Return: number
 */
int p_d(int in, int f)
{
	int (*__puc)(char) = _puc;
	int i, co = 0;
	unsigned int _abs_, cur;

	if (f == STDERR_FILENO)
		__puc = _epc;
	if (in < 0)
	{
		_abs_ = -in;
		__puc('-');
		co++;
	}
	else
		_abs_ = in;
	cur = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__puc('0' + cur / i);
			co++;
		}
		cur %= i;
	}
	__puc('0' + cur);
	co++;

	return (co);
}

/**
 * con_n - conv
 * @nu: the number
 * @b: the  base
 * @f: arg
 *
 * Return: string
 */
char *con_n(long int nu, int b, int f)
{
	static char *ar;
	static char buffer[50];
	char si = 0;
	char *p;
	unsigned long n = nu;

	if (!(f & CONVERT_UNSIGNED) && nu < 0)
	{
		n = -nu;
		si = '-';

	}
	ar = f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buffer[49];
	*p = '\0';

	do	{
		*--p = ar[n % b];
		n /= b;
	} while (n != 0);

	if (si)
		*--p = si;
	return (p);
}

/**
 * re_co - functi
 * @b: addres
 *
 * Return: Always 0;
 */
void re_co(char *b)
{
	int i;

	for (i = 0; b[i] != '\0'; i++)
		if (b[i] == '#' && (!i || b[i - 1] == ' '))
		{
			b[i] = '\0';
			break;
		}
}
