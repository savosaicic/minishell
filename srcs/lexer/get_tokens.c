#include "minishell.h"

static void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

/*
** t_list cmd_lst->content points to a t_cmd struct
** This function parse the token list made by the lexer
** to get a list of commands
*/
t_list	*parse_tokens(t_prg *prg, t_list *token_lst)
{
	t_list	*cmd_lst;
	t_cmd	*cmd;
	int		i;
	
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		exit_failure(prg, "sh: insufficient memory", 1);
	cmd->args = (char **)malloc(sizeof(char *) * (ft_lstsize(token_lst) + 1));
	if (!cmd->args)
		exit_failure(prg, "sh: insufficient memory", 1);
	i = 0;
	cmd_lst = NULL;
	while (token_lst)
	{
		cmd->args[i] = ft_strdup(((t_token *)token_lst->content)->token);
		token_lst = token_lst->next;
		i++;
	}
	ft_lstadd_back(&cmd_lst, ft_lstnew((void *)cmd));
	cmd->args[i] = NULL;
	return (cmd_lst);
}

t_ttype		get_token_type(char *token)
{
	if (!ft_strcmp(token, "|"))
		return (T_PIPE);
//	else if (!ft_strcmp(token, "<") || !ft_strcmp(token, ">"))
//		return (T_OPERATOR);
	else
		return (T_WORD);
}

t_token	*write_token(char *token)
{
	t_token	*token_struct;

	token_struct = malloc(sizeof(*token_struct));
	if (!token_struct)
		return (NULL);
	token_struct->token = ft_strdup(token);
	token_struct->token_type = get_token_type(token);
	return (token_struct);
}

t_list	*get_token(char *cmd_buffer)
{
	char	**tokens;
	t_list	*token_lst;
	int		i;

	tokens = ft_split(cmd_buffer, ' ');
	if (!tokens)
		return(NULL);
	i = 0;
	token_lst = NULL;
	while (tokens[i])
	{
		ft_lstadd_back(&token_lst, ft_lstnew(write_token(tokens[i])));
		i++;
	}
	free_tokens(tokens);
	return (token_lst);
}