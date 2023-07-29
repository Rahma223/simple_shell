#include "shell.h"

/**
 * cl_in - initia
 * @in: str
 */
void cl_in(info_t *in)
{
	in->arg = NULL;
	in->argv = NULL;
	in->path = NULL;
	in->argc = 0;
}

/**
 * se_in - ct
 * @in: a struct a
 * @a: argume
 */
void se_in(info_t *in, char **a)
{
	int i = 0;

	in->fname = a[0];
	if (in->arg)
	{
		/*in->argv = strtow(in->arg, " \t");*/
		if (!in->argv)
		{
			in->argv = malloc(sizeof(char *) * 2);
			if (in->argv)
			{
				in->argv[0] = _strdu(in->arg);
				in->argv[1] = NULL;
			}
		}
		for (i = 0; in->argv && in->argv[i]; i++)
			;
		in->argc = i;

		rep_al(in);
		rep_v(in);
	}
}

/**
 * fr_in - frees info_t
 * @in: struc
 * @al: true i
 */
void fr_in(info_t *in, int al)
{
	ffree(in->argv);
	in->argv = NULL;
	in->path = NULL;
	if (al)
	{
		if (!in->cmd_buf)
			free(in->arg);
		if (in->env)
			fr_li(&(in->env));
		if (in->history)
			fr_li(&(in->history));
		if (in->alias)
			fr_li(&(in->alias));
		ffree(in->environ);
			in->environ = NULL;
		bfree((void **)in->cmd_buf);
		if (in->readfd > 2)
			close(in->readfd);
		_puc(BUF_FLUSH);
	}
}
