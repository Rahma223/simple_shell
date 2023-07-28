#include "shell.h"

/**
 * myen - print
 * @in: Structure c
 * Return: Always 0
 */
int myen(info_t *in)
{
	print_list_str(in->env);
	return (0);
}

/**
 * gete - gets
 * @in: a Structure
 * @na: env va
 *
 * Return: the v
 */
char *gete(info_t *in, const char *na)
{
	list_t *n = in->env;
	char *pa;

	while (n)
	{
		pa = starts_with(n->str, na);
		if (pa && *pa)
			return (pa);
		n = n->next;
	}
	return (NULL);
}

/**
 * mys - Initi
 * @in: Structu
 *  Return: Always 0
 */
int mys(info_t *in)
{
	if (in->argc != 3)
	{
		_ep("Incorrect number of arguements\n");
		return (1);
	}
	if (_set(in, in->argv[1], in->argv[2]))
		return (0);
	return (1);
}

/**
 * myu - Remov
 * @in: Struct
 * Return: Always 0
 */
int myu(info_t *in)
{
	int i;

	if (in->argc == 1)
	{
		_ep("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= in->argc; i++)
		_uns(in, in->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
