#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delim
 * @in: the parameter struct
 * @bu: the char 
 * @p: address of current position in bu
 *
 * Return:  return the delim
 */
int is_chain(info_t *in, char *bu, size_t *P)
{
	size_t j = *P;

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
	else if (bu[j] == ';') /* found end of this command */
	{
		bu[j] = 0; /* replace semicolon with null */
		in->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @in: the parameter struct
 * @bu: the char buf
 * @p: address of current position in bu
 * @i: starting position in bu
 * @len: len of bu
 *
 * Return: Void
 */
void check_chain(info_t *in, char *bu, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (in->cmd_buf_type == CMD_AND)
	{
		if (in->status)
		{
			bu[i] = 0;
			j = len;
		}
	}
	if (in->cmd_buf_type == CMD_OR)
	{
		if (!in->status)
		{
			bu[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @in: the parameter struct
 *
 * Return: 1 if replaced
 */
int replace_alias(info_t *in)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(in->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		in->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @in: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *in)
{
	int i = 0;
	list_t *node;

	for (i = 0; in->argv[i]; i++)
	{
		if (in->argv[i][0] != '$' || !in->argv[i][1])
			continue;

		if (!_strcmp(in->argv[i], "$?"))
		{
			replace_string(&(in->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(in->argv[i], "$$"))
		{
			replace_string(&(in->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &in->argv[i][1], '=');
		if (node)
		{
			replace_string(&(in->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&in->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
