#include "minishell.h"


static t_cmd	*init_cmd_struct(int args_num)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = (char **)malloc(sizeof(char *) * (args_num + 1));
	if (!cmd->args)
		return (NULL);
	cmd->r_io[0] = STDIN_FILENO;
	cmd->r_io[1] = STDOUT_FILENO;
	return (cmd);
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
	
	(void)prg;
	cmd = init_cmd_struct(ft_lstsize(token_lst));
	if (!cmd)
		return (NULL);

	i = 0;
	cmd_lst = NULL;
	while (token_lst)
	{
		if (CAST(token_lst, t_token*)->token_type == T_REDIRECT)
		{
			if (parse_redirection(&cmd, &token_lst) > 0)
				(void)i; //delete the actual cmd and go to next one if there is a pipe
		}
		else if (CAST(token_lst, t_token*)->token_type == T_PIPE)
		{
			cmd->args[i] = NULL;
			ft_lstadd_back(&cmd_lst, ft_lstnew((void *)cmd));
			cmd = init_cmd_struct(ft_lstsize(token_lst));
			i = 0;
			token_lst = token_lst->next;
		}
		else
		{
			if ((CAST(token_lst, t_token*)->token_type == T_ASSIGN && i >= 1)
				|| (CAST(token_lst, t_token*)->token_type != T_ASSIGN))
			{
				cmd->args[i] = ft_strdup(((t_token *)token_lst->content)->token);
				i++;
			}
			token_lst = token_lst->next;
		}
	}
	if (cmd->args[0])
	{
		cmd->args[i] = NULL;
		ft_lstadd_back(&cmd_lst, ft_lstnew((void *)cmd));
	}
	return (cmd_lst);
}
