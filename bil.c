#include "shell.h"

/**
 * exit_t - for exiting
 * @i: struct varible
 * Return: exiting
 */

int exit_t(i_tt *i)
{
	int ch;

	if (i->argv[1])
	{
		ch = err_t(i->argv[1]);
		if (ch == -1)
		{
			i->status = 2;
			print_e(i, "legal number:");
			put_t(i->argv[1]);
			put_ch('\n');
			return (1);
		}
		i->err_num = err_t(i->argv[1]);
		return (-2);
	}
	i->err_num = -1;
	return (-2);
}

/**
 * cd_t - changes the directory
 * @i: struct variable
 * Return: 0
 */

int cd_t(i_tt *i)
{
	char *c, *d, buffer[1024];
	int ch;

	c = getcwd(buffer, 1024);
	if (!c)
		put_t("TODO: >>getcwd failure emsg here<<\n");
	if (!i->argv[1])
	{
		d = get_env(i, "HOME");
		if (!d)
			ch = chdir((d = get_env(i, "PWD=")) ? d : "/");
		else
			ch = chdir(d);
	}
	else if (_strcmp(i->argv[1], "_") == 0)
	{
		if (!get_env(i, "OLD"))
		{
			put_t(c);
			_putchar('\n');
			return (1);
		}
		put_t(get_env(i, "OLD")), _putchar('\n');
		ch = chdir((d = get_env(i, "OLD")) ? d : "/");
	}
	else
		ch = chdir(i->argv[1]);
	if (ch == -1)
	{
		print_e(i, "can't cd");
		put_t(i->argv[1]), put_ch('\n');
	}
	else
	{
		_setenv(i, "OLDp", get_env(i, "PWD="));
		_setenv(i, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * help_t - chenge dir
 * @i: struct variable
 * Return: 0
 */

int help_t(i_tt *i)
{
	char **arr;

	arr = i->argv;
	put_t("help\n");
	if (0)
		put_t(*arr);
	return (0);
}
