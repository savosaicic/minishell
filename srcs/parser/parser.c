#include "minishell.h"

t_cmd	*init_cmd_struct(int args_num)
{
	t_cmd *cmd;

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

int	is_a_redirection_token(t_ttype token_type)
{
	if (token_type == T_REDIRECT || token_type == T_DGREAT)
		return (1);
	return (0);
}

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
		if (CAST((token_lst), t_token *)->token_type == T_DLESS)
			parse_heredoc(&token_lst, &cmd);
		else if (is_a_redirection_token(CAST(token_lst, t_token *)->token_type))
			parse_redirection(&token_lst, &cmd);
		else if (CAST(token_lst, t_token *)->token_type == T_PIPE)
			parse_pipe(&token_lst, &cmd, &cmd_lst, &i);
		else
			parse_argument(&token_lst, &cmd, &i);
	}
	if (cmd->args[0])
		add_last_cmd(&cmd, &cmd_lst, i);
	return (cmd_lst);
}
