#include "shell.h"

/**
 * lis_len - determin
 * @ha: point
 *
 * Return: size
 */
size_t lis_len(const list_t *ha)
{
	size_t i = 0;

	while (ha)
	{
		ha = ha->next;
		i++;
	}
	return (i);
}

/**
 * l_to_s - returns an
 * @h: poin
 *
 * Return: array
 */
char **l_to_s(list_t *h)
{
	list_t *n = h;
	size_t i = lis_len(h), j;
	char **str;
	char *s;

	if (!h || !i)
		return (NULL);
	str = malloc(sizeof(char *) * (i + 1));
	if (!str)
		return (NULL);
	for (i = 0; n; n = n->next, i++)
	{
		s = malloc(_str(n->str) + 1);
		if (!s)
		{
			for (j = 0; j < i; j++)
				free(str[j]);
			free(str);
			return (NULL);
		}

		s = _str(s, n->str);
		str[i] = s;
	}
	str[i] = NULL;
	return (str);
}


/**
 * pr_l - prints
 * @ha: pointe
 *
 * Return: int
 */
size_t pr_l(const list_t *ha)
{
	size_t i = 0;

	while (ha)
	{
		_pu(con_n(h->num, 10, 0));
		_puc(':');
		_puc(' ');
		_pu(h->str ? ha->str : "(nil)");
		_pu("\n");
		ha = ha->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - returns
 * @n: pointe
 * @pre: strin
 * @ca: the next
 *
 * Return: match
 */
list_t *node_starts_with(list_t *n, char *pre, char ca)
{
	char *pa = NULL;

	while (n)
	{
		pa = s_w(n->str, pre);
		if (pa && ((ca == -1) || (*pa == ca)))
			return (n);
		n = n->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets thee
 * @h: point
 * @n: point
 *
 * Return: index of n
 */
ssize_t get_node_index(list_t *h, list_t *n)
{
	size_t i = 0;

	while (h)
	{
		if (h == n)
			return (i);
		h = h->next;
		i++;
	}
	return (-1);
}
