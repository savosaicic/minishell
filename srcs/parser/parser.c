#include "minishell.h"

t_cmd	*init_cmd_struct(int args_num)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);

	// while (((t_cmd *)cmd_struct)->args[i] != NULL)
	cmd->path = NULL;
	cmd->args = (char **)malloc(sizeof(char *) * (args_num + 1));
	if (!cmd->args)
		return (NULL);

	i = 0;
	while (i < args_num + 1)
		cmd->args[i++] = NULL;
	cmd->r_io[0] = STDIN_FILENO;
	cmd->r_io[1] = STDOUT_FILENO;
	return (cmd);
}

int	is_a_redirection_token(t_ttype token_type)
{
	if (token_type == T_REDIRECT || token_type == T_DGREAT)
		return (1);
	return (0);
}

/*
** t_list cmd_lst->content points to a t_cmd struct
** This function parse the token list made by the lexer
** to get a list of commands
*/
t_list	*parse_tokens(t_list *token_lst)
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
		if (CAST((token_lst), t_token *)->token_type == T_DLESS)
			parse_heredoc(&token_lst, &cmd);
		else if (is_a_redirection_token(CAST(token_lst, t_token *)->token_type))
			parse_redirection(&token_lst, &cmd, &i);
		else if (CAST(token_lst, t_token *)->token_type == T_PIPE)
			parse_pipe(&token_lst, &cmd, &cmd_lst, &i);
		else
			parse_argument(&token_lst, &cmd, &i);
	}
	if (cmd && cmd->args[0])
		add_last_cmd(&cmd, &cmd_lst, i);
//	print_cmd_lst(cmd_lst);
	return (cmd_lst);
}
