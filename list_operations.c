#include "main.h"

/**
 * add_new_node_end - adds a separator found at the end
 * of a sep_list.
 * @head: pointer to a pointer to the head of the list.
 * @sep: separator character (;, |, or &).
 * Return: address of head.
 */
sep_list *add_new_node_end(sep_list **head, char sep)
{
	sep_list *new, *temp;

	new = malloc(sizeof(sep_list));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_sep_list - frees a sep_list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_sep_list(sep_list **head)
{
	sep_list *temp;
	sep_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * add_line_node_end - adds a command line at the end
 * of a node_list.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
node_list *add_line_node_end(node_list **head, char *line)
{
	node_list *new, *temp;

	new = malloc(sizeof(node_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_node_list - frees a node_list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_node_list(node_list **head)
{
	node_list *temp;
	node_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
