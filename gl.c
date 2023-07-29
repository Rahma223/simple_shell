#include "shell.h"

/**
 * i_bu - the char
 * @in: the par
 * @b: a addre
 * @l: a addres
 * Return: a bytes
 */
ssize_t i_bu(info_t *in, char **b, size_t *l)
{
	ssize_t ra = 0;
	size_t l_p = 0;

	if (!*l)
	{
		free(*b);
		*b = NULL;
		signal(SIGINT, sig);
#if USE_GETLINE
		ra = getline(b, &l_p, stdin);
#else
		ra = _getl(in, b, &l_p);
#endif
		if (ra > 0)
		{
			if ((*b)[ra - 1] == '\n')
			{
				(*b)[ra - 1] = '\0';
				ra--;
			}
			in->linecount_flag = 1;
			re_co(*b);
			b_his_l(in, *b, in->histcount++);
			{
				*l = ra;
				in->cmd_buf = b;
			}
		}
	}
	return (ra);
}

/**
 * g_in - the gets
 * @in: a param
 *
 * Return: the byt
 */
ssize_t g_in(info_t *in)
{
	static char *b;
	static size_t i, j, l;
	ssize_t ra = 0;
	char **b_p = &(in->arg), *pa;

	_puc(BUF_FLUSH);
	ra = i_bu(in, &b, &l);
	if (ra == -1)
		return (-1);
	if (l)
	{
		j = i;
		pa = b + i;

		c_cha(in, b, &j, i, l);
		while (j < l)
		{
			if (is_ch(in, b, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= l)
		{
			i = l = 0;
			in->cmd_buf_type = CMD_NORM;
		}

		*b_p = pa;
		return (_str(pa));
	}

	*b_p = b;
	return (ra);
}

/**
 * re_b - the reads
 * @in: a param
 * @b: the buffer
 * @ia: a size
 *
 * Return: a size
 */
ssize_t re_b(info_t *in, char *b, size_t *ia)
{
	ssize_t ra = 0;

	if (*ia)
		return (0);
	ra = read(in->readfd, b, READ_BUF_SIZE);
	if (ra >= 0)
		*ia = ra;
	return (ra);
}

/**
 * _getl - to gets
 * @in: a par
 * @p: a address
 * @l: size
 *
 * Return: ssi
 */
int _getl(info_t *in, char **p, size_t *l)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t ka;
	ssize_t ra = 0, sa = 0;
	char *pa = NULL, *n_p = NULL, *ca;

	pa = *p;
	if (pa && l)
		sa = *l;
	if (i == len)
		i = len = 0;

	ra = re_b(in, buf, &len);
	if (ra == -1 || (ra == 0 && len == 0))
		return (-1);

	ca = strch(buf + i, '\n');
	ka = ca ? 1 + (unsigned int)(ca - buf) : len;
	n_p = _re(pa, sa, sa ? sa + ka : ka + 1);
	if (!n_p)
		return (pa ? free(pa), -1 : -1);

	if (sa)
		_strnc(n_p, buf + i, ka - i);
	else
		_stn(n_p, buf + i, ka - i + 1);

	sa += ka - i;
	i = ka;
	pa = n_p;

	if (l)
		*l = sa;
	*p = pa;
	return (sa);
}

/**
 * sig - a blocks
 * @s_n: the sig
 *
 * Return: va oid
 */
void sig(__attribute__((unused))int s_n)
{
	_pu("\n");
	_pu("$ ");
	_puc(BUF_FLUSH);
}
