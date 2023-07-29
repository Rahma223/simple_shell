#include "shell.h"

/**
 * hsh - main
 * @in: the p
 * @v: the argumen
 *
 * Return: 0 on success
 */
int hsh(info_t *in, char **v)
{
	ssize_t ra = 0;
	int b_ret = 0;

	while (ra != -1 && b_ret != -2)
	{
		cl_in(in);
		if (inter(in))
			_pu("$ ");
		_epc(BUF_FLUSH);
		ra = g_in(in);
		if (ra != -1)
		{
			se_in(in, v);
			b_ret = f_buil(in);
			if (b_ret == -1)
				fi_cm(in);
		}
		else if (inter(in))
			_puc('\n');
		fr_in(in, 0);
	}
	wr_his(in);
	fr_in(in, 1);
	if (!inter(in) && in->status)
		exit(in->status);
	if (b_ret == -2)
	{
		if (in->err_num == -1)
			exit(in->status);
		exit(in->err_num);
	}
	return (b_ret);
}

/**
 * f_buil - finds
 * @in: the paramete
 *
 * Return: -1 if builtin
 */
int f_buil(info_t *in)
{
	int i, b_in_ret = -1;
	builtin_table bu[] = {
		{"exit", mye},
		{"env", myen},
		{"help", myh},
		{"history", myhis},
		{"setenv", mys},
		{"unsetenv", myu},
		{"cd", myc},
		{NULL, NULL}
	};

	for (i = 0; bu[i].type; i++)
		if (strc(in->argv[0], bu[i].type) == 0)
		{
			in->line_count++;
			b_in_ret = bu[i].func(in);
			break;
		}
	return (b_in_ret);
}

/**
 * fi_cm - finds
 * @in: the parameter
 *
 * Return: void
 */
void fi_cm(info_t *in)
{
	char *pa = NULL;
	int i, k;

	in->path = in->argv[0];
	if (in->linecount_flag == 1)
	{
		in->line_count++;
		in->linecount_flag = 0;
	}
	for (i = 0, k = 0; in->arg[i]; i++)
		if (!is_de(in->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	pa = find_p(in, gete(in, "PATH="), in->argv[0]);
	if (pa)
	{
		in->path = pa;
		for_cm(in);
	}
	else
	{
		if ((inter(in) || gete(in, "PATH=")
					|| in->argv[0][0] == '/') && is_cm(in, in->argv[0]))
			for_cm(in);
		else if (*(in->arg) != '\n')
		{
			in->status = 127;
			p_err(in, "not found\n");
		}
	}
}

/**
 * for_cm - forks a an exec
 * @in: nfo struct
 *
 * Return: void
 */
void for_cm(info_t *in)
{
	pid_t ch_pid;

	ch_pid = fork();
	if (ch_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (ch_pid == 0)
	{
		if (execve(in->path, in->argv, g_env(in)) == -1)
		{
			fr_in(in, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(in->status));
		if (WIFEXITED(in->status))
		{
			in->status = WEXITSTATUS(in->status);
			if (in->status == 126)
				p_err(in, "Permission denied\n");
		}
	}
}
