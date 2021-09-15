#include "minishell.h"

t_ttype		get_token_type(char *token)
{
	if (!ft_strcmp(token, "|"))
		return (T_PIPE);
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












t_token	*init_token_struct(char *token)
{
	t_token	*token_struct;

	token_struct = malloc(sizeof(t_token));
	if (!token_struct)
		return (NULL);
	token_struct->token = ft_strdup(token);
	if (!token_struct)
		return (NULL);
	token_struct->token_type = UNIDENTIFIED;
	return (token_struct);
}




t_list	*get_token(char *cmd_buffer)
{
	char	**tokens;
	t_list	*token_lst;
	int		i;

	tokens = ft_split(cmd_buffer, ' ');
	if (!tokens)
		return (NULL);

	token_lst = NULL;
	i = 0;
	while (tokens[i])
	{
		ft_lstadd_back(&token_lst, ft_lstnew(init_token_struct(tokens[i])));
		i++;
	}
	free_tokens(tokens);
	return (token_lst);
}
