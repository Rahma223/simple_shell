#include "shell.h"

/**
 * is_cm - determines if
 * @in: the info
 * @p: path
 *
 * Return: 1 if true
 */
int is_cm(info_t *in, char *p)
{
	struct stat st;

	(void)in;
	if (!p || stat(p, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_ch - duplicates ch
 * @p: the PAing
 * @st:  index
 * @sp: stop
 *
 * Return: pointer
 */
char *dup_ch(char *p, int st, int sp)
{
	static char buf[1024];
	int i = 0, ka = 0;

	for (ka = 0, i = st; i < sp; i++)
		if (p[i] != ':')
			buf[k++] = p[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_p - finds this
 * @in: the
 * @p: the PAT
 * @cm: the cmd t
 *
 * Return: full path
 */
char *find_p(info_t *in, char *p, char *cm)
{
	int i = 0, curr_p = 0;
	char *pa;

	if (!p)
		return (NULL);
	if ((_str(cm) > 2) && s_w(cm, "./"))
	{
		if (is_cm(in, cm))
			return (cm);
	}
	while (1)
	{
		if (!p[i] || p[i] == ':')
		{
			pa = dup_ch(p, curr_p, i);
			if (!*pa)
				_strc(pa, cm);
			else
			{
				_strc(pa, "/");
				_strc(pa, cm);
			}
			if (is_cm(in, pa))
				return (pa);
			if (!p[i])
				break;
			curr_p = i;
		}
		i++;
	}
	return (NULL);
}
