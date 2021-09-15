#include "minishell.h"

int		is_cmd_sep(t_ttype type)
{
	return (type == T_PIPE);
}

static t_cmd	*init_cmd_struct(int args_num)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = (char **)malloc(sizeof(char *) * (args_num + 1));
	if (!cmd->args)
		return (NULL);

	return (cmd);
}

/*
** t_list cmd_lst->content points to a t_cmd struct
** This function parse the token list made by the lexer
** to get a list of commands
** THIS COMMENT IS DEPRECATED
*/
t_list	*parse_tokens(t_list *token_lst)
{
	t_list	*cmd_lst;
	t_cmd	*cmd;
	int		i;
	
	cmd = init_cmd_struct(ft_lstsize(token_lst));
	if (!cmd)
		return (NULL);

	i = 0;
	cmd_lst = NULL;
	while (token_lst)
	{
		cmd->args[i] = ft_strdup(((t_token *)token_lst->content)->token);
		token_lst = token_lst->next;
		i++;
		ft_lstadd_back(&cmd_lst, ft_lstnew((void *)cmd));
	}
	cmd->args[i] = NULL;
	return (cmd_lst);
}
