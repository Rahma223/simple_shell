#include "shell.h"

/**
 * main - ry point
 * @c: arg ct
 * @v: arg ve
 *
 * Return: 0 on success, 1 on error
 */
int main(int c, char **v)
{
	info_t in[] = { INFO_INIT };
	int f = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (f)
			: "r" (f));

	if (c == 2)
	{
		f = open(v[1], O_RDONLY);
		if (f == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_ep(v[0]);
				_ep(": 0: Can't open ");
				_ep(v[1]);
				_epc('\n');
				_epc(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		in->readfd = f;
	}
	popu(in);
	re_his(in);
	hsh(in, v);
	return (EXIT_SUCCESS);
}
