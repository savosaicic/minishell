#include "minishell.h"

void	reset_cmd_and_jump_to_next(t_cmd **cmd, int *args_index, t_list **token_lst)
{
	int	i;

	if (!cmd || !*cmd)
		return ;
	i = 0;
	while (((t_cmd *)(*cmd))->args[i] != NULL)
	{
		free(((t_cmd *)(*cmd))->args[i]);
		((t_cmd *)(*cmd))->args[i] = NULL;
		i++;
	}
	free(((t_cmd *)(*cmd))->path);
	((t_cmd *)(*cmd))->path = NULL;

	if ((*cmd)->r_io[0] != STDIN_FILENO)
		ft_close((*cmd)->r_io[0]);
	if ((*cmd)->r_io[1] != STDOUT_FILENO)
		ft_close((*cmd)->r_io[1]);
	(*cmd)->r_io[0] = STDIN_FILENO;
	(*cmd)->r_io[1] = STDOUT_FILENO;
	*args_index = 0;
	while (CAST((*token_lst), t_token *)->token_type != T_PIPE)
		*token_lst = (*token_lst)->next;
	*token_lst = (*token_lst)->next;
}

static int	redirect_input(t_list **token_lst, t_cmd **cmd, int *i)
{
	if ((*cmd)->r_io[0] != STDIN_FILENO)
		ft_close((*cmd)->r_io[0]);
	*token_lst = (*token_lst)->next;

	//Check for $, expand if so
	(*cmd)->r_io[0] = open(CAST((*token_lst), t_token*)->token, O_RDONLY);
	if ((*cmd)->r_io[0] < 0)
	{
		puterror(CAST((*token_lst), t_token*)->token, strerror(errno), 1);
		if (is_token_in_list(*token_lst, T_PIPE))
			reset_cmd_and_jump_to_next(cmd, i, token_lst);
		else
		{
			clear_cmd_struct(*cmd);
			while (*token_lst)
				*token_lst = (*token_lst)->next;
			*cmd = NULL;
		}
		return (1);
	}
	
	*token_lst = (*token_lst)->next;
	return (0);
}

static int	redirect_output(t_list **token_lst, t_cmd **cmd, int o_flags, int *i)
{
	if ((*cmd)->r_io[1] != STDOUT_FILENO)
		ft_close((*cmd)->r_io[1]);

	*token_lst = (*token_lst)->next;

	//Check for $, expand if so
	(*cmd)->r_io[1] = open(CAST((*token_lst), t_token*)->token, o_flags, 0644);
	if ((*cmd)->r_io[1] < 0)
	{
		puterror(CAST((*token_lst), t_token*)->token, strerror(errno), 1);
		if (is_token_in_list(*token_lst, T_PIPE))
			reset_cmd_and_jump_to_next(cmd, i, token_lst);
		else
		{
			clear_cmd_struct(*cmd);
			while (*token_lst)
				*token_lst = (*token_lst)->next;
			*cmd = NULL;
		}
		return (1);
	}
	*token_lst = (*token_lst)->next;
	return (0);
}

int		handle_redirection(t_cmd **cmd, t_list **token_lst, int *i)
{
	int	o_flags;

	o_flags = O_CREAT | O_TRUNC | O_RDWR;
	if (CAST((*token_lst), t_token*)->token_type == T_DGREAT)
		o_flags = O_CREAT | O_APPEND | O_RDWR;

	if (*CAST((*token_lst), t_token*)->token == '<')
		return (redirect_input(token_lst, cmd, i));
	else
		return (redirect_output(token_lst, cmd, o_flags, i));
	return (0);
}
