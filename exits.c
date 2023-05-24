#include "shell.h"

/**
 * str_cp - cop string
 * @ds: the string
 * @ss: the source
 * @n: the amount
 * Return: the sstring
 */

char *str_cp(char *ds, char *ss, int n)
{
	int ii, jj;
	char *ss = ds;

	ii = 0;
	while (ss[ii] != '\0' && ii < n - 1)
	{
		ds[ii] = ss[ii];
		ii++;
	}
	if (ii < n)
	{
		jj = ii;
		while (jj < n)
		{
			ds[jj] = '\0';
			jj++;
		}
	}
	return (ss);
}

/**
 * *str_ca - concatenates strings
 * @ds: the f string
 * @ss: the s string
 * @n: the amount
 * Return: the string
 */

char *str_ca(char *ds, char *ss, int n)
{
	int ii, jj;
	char *ss = ds;

	ii = 0;
	jj = 0;
	while (ds[ii] != '\0')
		ii++;
	while (ss[jj] != '\0' && jj < n)
	{
		ds[ii] = ss[jj];
		ii++;
		jj++;
	}
	if (jj < n)
		ds[ii] = '\0';
	return (ss);
}

/**
 * *str_ch - locates a char
 * @ss: the string
 * @cc: the char
 * Return: a pointer to memory
 */

char *str_ch(char *ss, char cc)
{
	do {
		if (*ss == cc)
			return (ss);
	} while (*ss++ != '\0');

	return (NULL);
}
