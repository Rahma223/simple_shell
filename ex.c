#include "shell.h"

/**
 **_stn - the copi
 *@d: the desti
 *@sa: the source
 *@na: the amount
 *Return: the conc
 */
char *_stn(char *d, char *sa, int na)
{
	int i, j;
	char *s = d;

	i = 0;
	while (sa[i] != '\0' && i < na - 1)
	{
		d[i] = sa[i];
		i++;
	}
	if (i < na)
	{
		j = i;
		while (j < na)
		{
			d[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strnc - conc
 *@d: the fig
 *@s: the sou
 *@na: the amou
 *Return: the con
 */
char *_strnc(char *d, char *s, int na)
{
	int i, j;
	char *sa = d;

	i = 0;
	j = 0;
	while (d[i] != '\0')
		i++;
	while (s[j] != '\0' && j < na)
	{
		d[i] = s[j];
		i++;
		j++;
	}
	if (j < na)
		d[i] = '\0';
	return (sa);
}

/**
 **strch - the locat
 *@sa: the str
 *@ca: the char
 *Return: (s) a poin
 */
char *strch(char *sa, char ca)
{
	do {
		if (*sa == ca)
			return (sa);
	} while (*sa++ != '\0');

	return (NULL);
}
