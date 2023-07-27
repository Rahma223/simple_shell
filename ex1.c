#include "shell.h"

/**
 * read_input - for reading
 * @line: a char
 * Return: nothing
 */

void read_input(char *line)
{
	printf("shell> ");
	fgets(line, MAX_INPUT_SIZE, stdin);
	line[strcspn(line, "\n")] = '\0';
}

/**
 * tokenize_input - token input
 * @line: a char
 * @tokens: a ttto
 * @num_tokens: a numbers of to
 * Return:nothing
 */

void tokenize_input(char *line, char **tokens, int *num_tokens)
{
	char *token = strtok(line, " ");
	*num_tokens = 0;
	while (token != NULL)
	{
		tokens[*num_tokens] = token;
		(*num_tokens)++;
		token = strtok(NULL, " ");
	}
	tokens[*num_tokens] = NULL;
}
