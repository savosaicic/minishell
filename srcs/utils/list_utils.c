#include "minishell.h"

t_tokenlst	*new_node(char *token)
{
	t_tokenlst	*node;

	node = malloc(sizeof(t_tokenlst));
	if (!node)
		return (NULL);
	node->token_type = get_token_type(token);
	node->token = ft_strdup(token);
	node->next = NULL;
	return (node);
}

int		lst_size(t_tokenlst	*head)
{
	int	size;

	size = 0;
	while (head)
	{
		head = head->next;
		size++;
	}
	return (size);
}

t_tokenlst	*get_last_node(t_tokenlst *head)
{
	t_tokenlst	*last;

	while (head->next)
		head = head->next;
	last = head;
	return (last);
}

void	delete_list(t_tokenlst **head)
{
	t_tokenlst	*tmp;

	if (!head)
		return ;
	else if (!*head)
		return ;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->token);
		free(tmp);
	}
	*head = NULL;
}

void	push_front(t_tokenlst **head, t_tokenlst *new_node)
{
	new_node->next = *head;
	*head = new_node;
}

void	push_back(t_tokenlst **head, t_tokenlst *new_node)
{
	t_tokenlst	*last_node;

	if (!head)
		return ;
	else if (!*head)
		*head = new_node;
	else
	{
		last_node = get_last_node(*head);
		last_node->next = new_node;
	}
}
