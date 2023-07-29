#include "shell.h"

/**
 * **strt - splits a stri
 * @s: the inp
 * @da: the deli
 * Return: a pointe
 */

char **strt(char *s, char *da)
{
	int i, j, ka, ma, num = 0;
	char **sa;

	if (s == NULL || s[0] == 0)
		return (NULL);
	if (!da)
		da = " ";
	for (i = 0; s[i] != '\0'; i++)
		if (!is_de(s[i], da) && (is_de(s[i + 1], da) || !s[i + 1]))
			num++;

	if (num == 0)
		return (NULL);
	sa = malloc((1 + num) * sizeof(char *));
	if (!sa)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (is_de(s[i], da))
			i++;
		ka = 0;
		while (!is_de(s[i + ka], da) && s[i + ka])
			ka++;
		sa[j] = malloc((ka + 1) * sizeof(char));
		if (!sa[j])
		{
			for (ka = 0; ka < j; ka++)
				free(sa[ka]);
			free(sa);
			return (NULL);
		}
		for (ma = 0; ma < ka; ma++)
			sa[j][ma] = s[i++];
		sa[j][ma] = 0;
	}
	sa[j] = NULL;
	return (sa);
}

/**
 * **strt2 - splits
 * @st: the in
 * @da: the var
 * Return: a pointer to an arra
 */
char **strt2(char *st, char da)
{
	int i, j, ka, ma, num = 0;
	char **sa;

	if (st == NULL || st[0] == 0)
		return (NULL);
	for (i = 0; st[i] != '\0'; i++)
		if ((st[i] != da && st[i + 1] == da) ||
				    (st[i] != da && !st[i + 1]) || st[i + 1] == da)
			num++;
	if (num == 0)
		return (NULL);
	sa = malloc((1 + num) * sizeof(char *));
	if (!sa)
		return (NULL);
	for (i = 0, j = 0; j < num; j++)
	{
		while (st[i] == da && st[i] != da)
			i++;
		ka = 0;
		while (st[i + ka] != da && st[i + ka] && st[i + ka] != da)
			ka++;
		sa[j] = malloc((ka + 1) * sizeof(char));
		if (!sa[j])
		{
			for (ka = 0; ka < j; ka++)
				free(sa[ka]);
			free(sa);
			return (NULL);
		}
		for (ma = 0; ma < ka; ma++)
			sa[j][ma] = st[i++];
		sa[j][ma] = 0;
	}
	sa[j] = NULL;
	return (sa);
}
