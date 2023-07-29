#include "shell.h"

/**
 * ad_no - add
 * @h: addrd node
 * @s: the str
 * @n: node inde
 *
 * Return: size
 */
list_t *ad_no(list_t **h, const char *s, int n)
{
	list_t *new_h;

	if (!h)
		return (NULL);
	new_h = malloc(sizeof(list_t));
	if (!new_h)
		return (NULL);
	_mem((void *)new_h, 0, sizeof(list_t));
	new_h->num = n;
	if (s)
	{
		new_h->str = _strdu(s);
		if (!new_h->str)
		{
			free(new_h);
			return (NULL);
		}
	}
	new_h->next = *h;
	*h = new_h;
	return (new_h);
}
/**
 * add_n - adds a
 * @h: address
 * @s: str fie
 * @nu: node in
 *
 * Return: size
 */
list_t *add_n(list_t **h, const char *s, int nu)
{
	list_t *new_n, *n;

	if (!h)
		return (NULL);

	n = *h;
	new_n = malloc(sizeof(list_t));
	if (!new_n)
		return (NULL);
	_mem((void *)new_n, 0, sizeof(list_t));
	new_n->num = nu;
	if (s)
	{
		new_n->str = _strdu(s);
		if (!new_n->str)
		{
			free(new_n);
			return (NULL);
		}
	}
	if (n)
	{
		while (n->next)
			n = n->next;
		n->next = new_n;
	}
	else
		*h = new_n;
	return (new_n);
}

/**
 * p_list_s - prints
 * @ha: pointer
 *
 * Return: size
 */
size_t p_list_s(const list_t *ha)
{
	size_t i = 0;

	while (ha)
	{
		_pu(ha->str ? ha->str : "(nil)");
		_pu("\n");
		ha = ha->next;
		i++;
	}
	return (i);
}
/**
 * delete_node_at_index - a delete
 * @h: addres
 * @in: index
 *
 * Return: 1 on succ
 */
int delete_node_at_index(list_t **h, unsigned int in)
{
	list_t *n, *prev_n;
	unsigned int i = 0;

	if (!h || !*h)
		return (0);

	if (!in)
	{
		n = *h;
		*h = (*h)->next;
		free(n->str);
		free(n);
		return (1);
	}
	n = *h;
	while (n)
	{
		if (i == in)
		{
			prev_n->next = n->next;
			free(n->str);
			free(n);
			return (1);
		}
		i++;
		prev_n = n;
		n = n->next;
	}
	return (0);
}

/**
 * fr_li - free
 * @h_ptr: addres
 *
 * Return: a void
 */
void fr_li(list_t **h_ptr)
{
	list_t *n, *next_n, *h;

	if (!h_ptr || !*h_ptr)
		return;
	h = *h_ptr;
	n = h;
	while (n)
	{
		next_n = n->next;
		free(n->str);
		free(n);
		n = next_n;
	}
	*h_ptr = NULL;
}
