#include "shell.h"

/**
 * env_t - print the environment
 * @i: struct var
 * Return: 0
 */

int env_t(i_tt *i)
{
	print_list_str(i->env);
	return (0);
}

/**
 * get_env - get the environ
 * @i: struct var
 * @nam: env name
 * Return: the value
 */

char *get_env(i_tt *i, const char *nam)
{
	lis_t *n = i->env;
	char *pp;

	while (n)
	{
		pp = starts_with(n->str, nam);
		if (pp && *pp)
			return (pp);
		n = n->next;
	}
	return (NULL);
}

/**
 * set_env - new environment
 * @i: struct var
 * Return: 0
 */

int set_env(i_tt *i)
{
	if (i->argc != 3)
	{
		put_t("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(i, i->argv[1], i->argv[2]))
		return (0);
	return (1);
}

/**
 * unset_env - remove environment
 * @i: struct var
 * Return: 0
 */

int unset_env(i_tt *i)
{
	int ii;

	if (i->argc == 1)
	{
		put_t("few arguements.\n");
		return (1);
	}
	for (ii = 1; ii <= i->argc; ii++)
		_unsetenv(i, i->argv[ii]);
	return (0);
}

/**
 * pop_env - populates env
 * @i: struct var
 * Return: 0
 */

int pop_env(i_tt *i)
{
	lis_t *n = NULL;
	size_t ii;

	for (ii = 0; environ[ii]; ii++)
		add_node_end(&n, environ[ii], 0);
	i->env = n;
	return (0);
}
