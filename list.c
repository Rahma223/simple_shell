#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: pointer to pointer
 * @str: string
 * @num: node
 * Return: size of list
 */
lis_t *add_node(lis_t **head, const char *str, int num)
{
	lis_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(lis_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(lis_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer
 * @str: string
 * @num: number
 * Return: size of list
 */
lis_t *add_node_end(lis_t **head, const char *str, int num)
{
	lis_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(lis_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(lis_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the str element of a linked list
 * @h: pointer to first node
 * Return: size of list
 */
size_t print_list_str(const lis_t *h)
{
	size_t i = 0;

	while (h)
	{
		put_t(h->str ? h->str : "(nil)");
		put_t("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer
 * @index: index
 * Return: 1 or 0
 */
int delete_node_at_index(lis_t **head, unsigned int index)
{
	lis_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: pointer to pointer
 * Return: void
 */
void free_list(lis_t **head_ptr)
{
	lis_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
