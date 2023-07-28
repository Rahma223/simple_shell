#include "shell.h"

/**
 * Is_chaiN - test if current char in buffer is a cha delim
 * @info: the para
 * @buf: the char buff
 * @p: address of current
 *
 * Return: 1 if chain delim
 */
int Is_chaiN(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHA;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * Check_chaiN - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void Check_chaiN(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * Replace_aliaS - replaces an aliases in the tokenized string
 * @info: the para
 *
 * Return: 1 if replaced
 */
int Replace_aliaS(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = Node_start_witH(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		Free(info->argv[0]);
		p = _StrchR(nod->str, '=');
		if (!p)
			return (0);
		p = _StrduP(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * Replace_varS - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced
 */
int Replace_varS(info_t *info)
{
	int i = 0;
	list_t *nod;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_StrcmP(info->argv[i], "$?"))
		{
			Replace_strinG(&(info->argv[i]),
				_StrduP(Convert_numbeR(info->status, 10, 0)));
			continue;
		}
		if (!_StrcmP(info->argv[i], "$$"))
		{
			Replace_strinG(&(info->argv[i]),
				_StrduP(Convert_numbeR(getpid(), 10, 0)));
			continue;
		}
		node = nodE_startS_witH(info->env, &info->argv[i][1], '=');
		if (nodE)
		{
			Replace_strinG(&(info->argv[i]),
				_StrduP(_StrchR(nodE->str, '=') + 1));
			continue;
		}
		Replace_strinG(&info->argv[i], _StrduP(""));

	}
	return (0);
}

/**
 * Replace_strinG - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replace,
 */
int Replace_strinG(char **old, char *new)
{
	Free(*old);
	*old = new;
	return (1);
}
