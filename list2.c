#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer
 * Return: size of list
 */
size_t list_len(const lis_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - returns an array of strings
 * @head: pointer
 * Return: array of strings
 */
char **list_to_strings(lis_t *head)
{
	lis_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a linked list
 * @h: pointer
 * Return: size of list
 */
size_t print_list(const lis_t *h)
{
	size_t i = 0;

	while (h)
	{
		put_t(conv_num(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		put_t(h->str ? h->str : "(nil)");
		put_t("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - returns node whose string
 * @node: pointer
 * @prefix: string
 * @c: the next character
 * Return: match node or null
 */
lis_t *node_starts_with(lis_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer
 * @node: pointer
 * Return: index of node
 */
ssize_t get_node_index(lis_t *head, lis_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
