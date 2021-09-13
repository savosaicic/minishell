#include "minishell.h"

t_ttype		get_token_type(char *token)
{
	if (!ft_strcmp(token, "|"))
	{
		printf("pipe\n");
		return (T_PIPE);
	}
	else if (!ft_strcmp(token, "<") || !ft_strcmp(token, ">"))
	{
		printf("redirection operator\n");
		return (T_OPERATOR);
	}
	else
		return (T_WORD);
}

static void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

t_cmd	*get_token(char *cmd_buffer)
{
	char	**tokens;
	t_cmd	*head;
	int		i;

	tokens = ft_split(cmd_buffer, ' ');
	if (!tokens)
		return (NULL);
	head = NULL;
	i = 0;
	while (tokens[i])
	{
		push_back(&head, new_node(tokens[i]));
		i++;
	}
	free_tokens(tokens);
	return (head);
}
