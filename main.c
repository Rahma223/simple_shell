#include "shell.h"
/**
 * main - the main
 * Return: a int
 */

int main(void)
{
	pid_t pid = fork();

	while (1)
	{
		char line[MAX_INPUT_SIZE];
		char *tokens[MAX_NUM_TOKENS];
		int num_tokens = 0;

		read_input(line);
		tokenize_input(line, tokens, &num_tokens);
		if (num_tokens == 0)
		{
			continue;
		}
		if (strcmp(tokens[0], "exit") == 0)
		{
			break;
		}
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execvp(tokens[0], tokens) == -1)
			{
				perror("execvp");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			int status;

			if (waitpid(pid, &status, 0) == -1)
			{
				perror("waitpid");
				exit(EXIT_FAILURE);
			}
		}
	}
	return (0);
}
