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
		ch = _erratoi(i->argv[1]);
		if (ch == -1)
		{
			i->status = 2;
			print_error(i, "legal number:");
			_eputs(i->argv[1]);
			_eputchar('\n');
			return (1);
		}
		i->err_num = _erratoi(i->argv[1]);
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
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!i->argv[1])
	{
		d = _getenv(i, "HOME");
		if (!d)
			ch = chdir((d = _getenv(i, "PWD=")) ? d : "/");
		else
			ch = chdir(d);
	}
	else if (_strcmp(i->argv[1], "_") == 0)
	{
		if (!_getenv(i, "OLD"))
		{
			_puts(c);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(i, "OLD")), _putchar('\n');
		ch = chdir((d = _getenv(i, "OLD")) ? d : "/");
	}
	else
		ch = chdir(i->argv[1]);
	if (ch == -1)
	{
		print_error(i, "can't cd");
		_eputs(i->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(i, "OLDp", _getenv(i, "PWD="));
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
	_puts("help\n");
	if (0)
		_puts(*arr);
	return (0);
}
