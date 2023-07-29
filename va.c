#include "shell.h"

/**
 * is_ch - test if current
 * @in: the par
 * @bu: the char
 * @Pa: addres
 *
 * Return: retur
 */
int is_ch(info_t *in, char *bu, size_t *Pa)
{
	size_t j = *Pa;

	if (bu[j] == '|' && bu[j + 1] == '|')
	{
		bu[j] = 0;
		j++;
		in->cmd_buf_type = CMD_OR;
	}
	else if (bu[j] == '&' && bu[j + 1] == '&')
	{
		bu[j] = 0;
		j++;
		in->cmd_buf_type = CMD_AND;
	}
	else if (bu[j] == ';')
	{
		bu[j] = 0;
		in->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*Pa = j;
	return (1);
}

/**
 * c_cha - checks we should
 * @in: the paramet
 * @bu: the buf
 * @pa: addre
 * @ia: starting
 * @len: len of bu
 *
 * Return: Void
 */
void c_cha(info_t *in, char *bu, size_t *pa, size_t ia, size_t len)
{
	size_t j = *pa;

	if (in->cmd_buf_type == CMD_AND)
	{
		if (in->status)
		{
			bu[ia] = 0;
			j = len;
		}
	}
	if (in->cmd_buf_type == CMD_OR)
	{
		if (!in->status)
		{
			bu[ia] = 0;
			j = len;
		}
	}

	*pa = j;
}

/**
 * rep_al - replace
 * @in: the paramet
 *
 * Return: 1 if replaced
 */
int rep_al(info_t *in)
{
	int i;
	list_t *n;
	char *pa;

	for (i = 0; i < 10; i++)
	{
		n = node_starts_with(in->alias, in->argv[0], '=');
		if (!n)
			return (0);
		free(in->argv[0]);
		pa = strch(n->str, '=');
		if (!pa)
			return (0);
		pa = _strdu(pa + 1);
		if (!pa)
			return (0);
		in->argv[0] = pa;
	}
	return (1);
}

/**
 * rep_v - replace
 * @in: the para
 *
 * Return: 1 if repla
 */
int rep_v(info_t *in)
{
	int i = 0;
	list_t *n;

	for (i = 0; in->argv[i]; i++)
	{
		if (in->argv[i][0] != '$' || !in->argv[i][1])
			continue;

		if (!strc(in->argv[i], "$?"))
		{
			rep_str(&(in->argv[i]),
				_strdu(con_n(in->status, 10, 0)));
			continue;
		}
		if (!strc(in->argv[i], "$$"))
		{
			rep_str(&(in->argv[i]),
				_strdu(con_n(getpid(), 10, 0)));
			continue;
		}
		n = node_starts_with(in->env, &in->argv[i][1], '=');
		if (n)
		{
			rep_str(&(in->argv[i]),
				_strdu(strch(n->str, '=') + 1));
			continue;
		}
		rep_str(&in->argv[i], _strdu(""));

	}
	return (0);
}

/**
 * rep_str - repla
 * @o: add
 * @n: new
 *
 * Return: 1 if
 */
int rep_str(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}
