#include "shell.h"

/**
 * hist_t - display the hist list
 * @i: struct variable
 * Return: 0
 */

int hist_t(i_tt *i)
{
	print_list(i->history);
	return (0);
}

/**
 * uns - usets alias
 * @i: struct variable
 * @ss: the string
 * Return: 0 if true
 */

int uns(i_tt *i, char *ss)
{
	char *pp, s;
	int r;

	pp = _strchr(ss, '=');
	if (!pp)
		return (1);
	s = *pp;
	*pp = 0;
	r = delet_node_at_index(&(i->alias),
			get_node_index(i->alias, node_starts_with(i->alias, ss, -1)));
	*pp = s;
	return (r);
}

/**
 * set_t - set alias
 * @i: struct varable
 * @ss: the string
 * Return: 0 if true
 */

int set_t(i_tt *i, char *ss)
{
	char *pp;

	pp = _strchr(ss, '=');
	if (!pp)
		return (1);
	if (!*++pp)
		return (uns(i, ss));

	uns(i, ss);
	return (add_node_end(&(i->alias), ss, 0) == NULL);
}

/**
 * print_t - print an alias
 * @n: the node
 * Return: 0
 */

int print_t(lis_t *n)
{
	char *pp = NULL, *s = NULL;

	if (n)
	{
		pp = _strchr(n->str, '=');
		for (s = n->str; s <= pp; s++)
		_putchar(*s);
		_putchar('\'');
		_puts(pp + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * ali - the alias
 * @i: struct var
 * Return: 0
 */

int ali(i_tt *i)
{
	int ii = 0;
	char *pp = NULL;
	lis_t *n = NULL;

	if (i->argc == 1)
	{
		n = i->alias;
		while (n)
		{
			print_t(n);
			n = n->next;
		}
		return (0);
	}
	for (ii = 1; i->argv[ii]; ii++)
	{
		pp = _strchr(i->argv[ii], '=');
		if (pp)
			set_t(i, i->argv[ii]);
		else
			print_t(node_starts_with(i->alias, i->argv[ii], '='));
	}

	return (0);
}
