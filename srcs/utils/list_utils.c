#include "minishell.h"

t_cmd	*new_node(char *token)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->token_type = get_token_type(token);
	node->token = ft_strdup(token);
	node->next = NULL;
	return (node);
}

int		lst_size(t_cmd	*head)
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

t_cmd	*get_last_node(t_cmd *head)
{
	t_cmd	*last;

	while (head->next)
		head = head->next;
	last = head;
	return (last);
}

void	delete_list(t_cmd **head)
{
	t_cmd	*tmp;

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

void	push_front(t_cmd **head, t_cmd *new_node)
{
	new_node->next = *head;
	*head = new_node;
}

void	push_back(t_cmd **head, t_cmd *new_node)
{
	t_cmd	*last_node;

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
