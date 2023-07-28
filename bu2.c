#include "shell.h"

/**
 * myhis - to dis
 * @in:a  Struct
 *  Return: Always 0
 */
int myhis(info_t *in)
{
	pr_l(in->history);
	return (0);
}

/**
 * un_al - thes sets
 * @in: parameter
 * @s: the string
 *
 * Return: Always
 */
int un_al(info_t *in, char *s)
{
	char *pa, ca;
	int r;

	pa = _strchr(s, '=');
	if (!pa)
		return (1);
	ca = *pa;
	*pa = 0;
	r = delete_node_at_index(&(in->alias),
		get_node_index(in->alias, node_starts_with(in->alias, s, -1)));
	*pa = ca;
	return (r);
}

/**
 * s_al - sets
 * @in: a parameter
 * @s: the string
 *
 * Return: Always 0
 */
int s_al(info_t *in, char *s)
{
	char *pa;

	pa = _strchr(s, '=');
	if (!pa)
		return (1);
	if (!*++pa)
		return (unset_alias(in, s));

	un_al(in, s);
	return (add_node_end(&(in->alias), s, 0) == NULL);
}

/**
 * p_al - prints
 * @n: the alia
 *
 * Return: Always 0
 */
int p_al(list_t *n)
{
	char *pa = NULL, *aa = NULL;

	if (n)
	{
		pa = _strchr(n->str, '=');
		for (aa = n->str; aa <= pa; aa++)
		_puc(*aa);
		_puc('\'');
		_pu(pc + 1);
		_pu("'\n");
		return (0);
	}
	return (1);
}

/**
 * myal - mimics
 * @in: a Structure
 *  Return: Always 0
 */
int myal(info_t *in)
{
	int i = 0;
	char *pa = NULL;
	list_t *n = NULL;

	if (in->argc == 1)
	{
		n = in->alias;
		while (n)
		{
			p_al(n);
			n = n->next;
		}
		return (0);
	}
	for (i = 1; in->argv[i]; i++)
	{
		pa = _strchr(in->argv[i], '=');
		if (pa)
			s_al(in, in->argv[i]);
		else
			p_al(node_starts_with(in->alias, in->argv[i], '='));
	}

	return (0);
}
