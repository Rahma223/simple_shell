#include "shell.h"

/**
 * mye - the exits
 * @in: the var
 * Return: exits to
 */
int mye(info_t *in)
{
	int ex;

	if (in->argv[1])
	{
		ex = err(in->argv[1]);
		if (ex == -1)
		{
			in->status = 2;
			p_err(in, "Illegal number: ");
			_ep(in->argv[1]);
			_epc('\n');
			return (1);
		}
		in->err_num = err(in->argv[1]);
		return (-2);
	}
	in->err_num = -1;
	return (-2);
}

/**
 * myc - th changes
 * @in: a Struc
 * Return: 0
 */
int myc(info_t *in)
{
	char *sa, *d, buffer[1024];
	int ch;

	sa = getcwd(buffer, 1024);
	if (!sa)
		_pu("TODO: >>getcwd failure emsg here<<\n");
	if (!in->argv[1])
	{
		d = gete(in, "HOME=");
		if (!d)
			ch = chdir((d = gete(in, "PWD=")) ? d : "/");
		else
			ch = chdir(d);
	}
	else if (strc(in->argv[1], "-") == 0)
	{
		if (!gete(in, "OLDPWD="))
		{
			_pu(sa);
			_puc('\n');
			return (1);
		}
		_pu(gete(in, "OLDPWD=")), _puc('\n');
		ch = chdir((d = gete(in, "OLDPWD=")) ? d : "/");
	}
	else
		ch = chdir(in->argv[1]);
	if (ch == -1)
	{
		p_err(in, "can't cd to ");
		_ep(in->argv[1]), _epc('\n');
	}
	else
	{
		_set(in, "OLDPWD", gete(in, "PWD="));
		_set(in, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * myh - the changes
 * @in: Structure
 * Return: Always 0
 */
int myh(info_t *in)
{
	char **ar;

	ar = in->argv;
	_pu("help call works. Function not yet implemented \n");
	if (0)
		_pu(*ar);
	return (0);
}
