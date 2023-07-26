#include "shell.h"

/**
 * main - the main function
 * Return: integer numbers
 */

int main(void)
{
	pid_t pid = fork();
	char buffer[BUFFER_SIZE];
	char *args[2];
	int status;

	while (1)
	{
		printf("simple_shell$ ");
		fflush(stdout);
		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
		{
			printf("\n");
			break;
		}
		buffer[strcspn(buffer, "\n")] = '\0';

		if (pid < 0)
		{
			perror("fork failed");
			continue;
		}
		else if (pid == 0)
		{
			args[0] = buffer;
			args[1] = NULL;
			if (execvp(args[0], args) < 0)
			{
				perror("execvp failed");
				exit(1);
			}
		}
		else
		{
			if (waitpid(pid, &status, 0) < 0)
			{
				perror("waitpid failed");
			}
		}
	}
	return (0);
}
