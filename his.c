#include "shell.h"

/**
 * get_his_f - gets
 * @in: a parame
 *
 * Return: allocate
 */

char *get_his_f(info_t *in)
{
	char *b, *d;

	d = gete(in, "HOME=");
	if (!d)
		return (NULL);
	b = malloc(sizeof(char) * (_str(d) + _str(HIST_FILE) + 2));
	if (!b)
		return (NULL);
	b[0] = 0;
	_st(b, d);
	_strc(b, "/");
	_strc(b, HIST_FILE);
	return (b);
}

/**
 * wr_his - a creates
 * @in: the parame
 *
 * Return: 1 on s
 */
int wr_his(info_t *in)
{
	ssize_t f;
	char *file = get_his_f(in);
	list_t *n = NULL;

	if (!file)
		return (-1);

	f = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file);
	if (f == -1)
		return (-1);
	for (n = in->history; n; n = n->next)
	{
		_pus(n->str, f);
		_puf('\n', f);
	}
	_puf(BUF_FLUSH, f);
	close(f);
	return (1);
}

/**
 * re_his - a read
 * @in: the para
 *
 * Return: histcount
 */
int re_his(info_t *in)
{
	int i, las = 0, lin = 0;
	ssize_t f, rd, fs = 0;
	struct stat st;
	char *b = NULL, *file = get_his_f(in);

	if (!file)
		return (0);

	f = open(file, O_RDONLY);
	free(file);
	if (f == -1)
		return (0);
	if (!fstat(f, &st))
		fs = st.st_size;
	if (fs < 2)
		return (0);
	b = malloc(sizeof(char) * (fs + 1));
	if (!b)
		return (0);
	rd = read(f, b, fs);
	b[fs] = 0;
	if (rd <= 0)
		return (free(b), 0);
	close(f);
	for (i = 0; i < fs; i++)
		if (b[i] == '\n')
		{
			b[i] = 0;
			b_his_l(in, b + las, lin++);
			las = i + 1;
		}
	if (las != i)
		b_his_l(in, b + las, lin++);
	free(b);
	in->histcount = lin;
	while (in->histcount-- >= HIST_MAX)
		delete_node_at_index(&(in->history), 0);
	ren_his(in);
	return (in->histcount);
}

/**
 * b_his_l - aa dds entr
 * @in: Structure conta
 * @b: buffer
 * @lin: the hist
 *
 * Return: Always 0
 */
int b_his_l(info_t *in, char *b, int lin)
{
	list_t *n = NULL;

	if (in->history)
		n = in->history;
	add_n(&n, b, lin);

	if (!in->history)
		in->history = n;
	return (0);
}

/**
 * ren_his - renumber
 * @in: Structur
 *
 * Return: the ne
 */
int ren_his(info_t *in)
{
	list_t *n = in->history;
	int i = 0;

	while (n)
	{
		n->num = i++;
		n = n->next;
	}
	return (in->histcount = i);
}
