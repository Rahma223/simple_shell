#include "shell.h"

/**
 * g_env - to returns
 * @in: Structure
 * Return: Always 0
 */
char **g_env(info_t *in)
{
	if (!in->environ || in->env_changed)
	{
		in->environ = l_to_s(in->env);
		in->env_changed = 0;
	}

	return (in->environ);
}

/**
 * _uns - to Remove
 * @in: Structur
 *  Return: 1 on dele
 * @v: the string
 */
int _uns(info_t *in, char *v)
{
	list_t *n = in->env;
	size_t i = 0;
	char *pa;

	if (!n || !v)
		return (0);

	while (n)
	{
		pa = s_w(n->str, v);
		if (pa && *pa == '=')
		{
			in->env_changed = delete_node_at_index(&(in->env), i);
			i = 0;
			n = in->env;
			continue;
		}
		n = n->next;
		i++;
	}
	return (in->env_changed);
}

/**
 * _set - the Initia
 * @in: a Structure
 * @v: the strin
 * @val: the str
 *  Return: Always 0
 */
int _set(info_t *in, char *v, char *val)
{
	char *b = NULL;
	list_t *n;
	char *pa;

	if (!v || !val)
		return (0);

	b = malloc(_str(v) + _str(val) + 2);
	if (!b)
		return (1);
	_st(b, v);
	_strc(b, "=");
	_strc(b, val);
	n = in->env;
	while (n)
	{
		pa = s_w(n->str, v);
		if (pa && *pa == '=')
		{
			free(n->str);
			n->str = b;
			in->env_changed = 1;
			return (0);
		}
		n = n->next;
	}
	add_n(&(in->env), b, 0);
	free(b);
	in->env_changed = 1;
	return (0);
}
