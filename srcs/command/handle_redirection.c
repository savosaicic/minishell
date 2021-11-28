#include "minishell.h"

static int	redirect_input(t_list **token_lst, t_cmd **cmd)
{
	if ((*cmd)->r_io[0] != STDIN_FILENO)
		close((*cmd)->r_io[0]);
	else if ((*cmd)->r_io[1] != STDOUT_FILENO)
		close((*cmd)->r_io[1]);
	*token_lst = (*token_lst)->next;
	if (!*token_lst || ((t_token*)(*token_lst)->content)->token_type == T_PIPE)
		return (write_error_msg("minishell", "parse error near \'<\'", NULL, 1));

	//Check for $, expand if so
	(*cmd)->r_io[0] = open(CAST((*token_lst), t_token*)->token, O_RDONLY);
	if ((*cmd)->r_io[0] < 0)
	{
		write_error_msg("minishell", CAST((*token_lst), t_token*)->token, strerror(errno), 1);
		return (1);
	}
	
	*token_lst = (*token_lst)->next;
	return (0);
}

static int	redirect_output(t_list **token_lst, t_cmd **cmd, int o_flags)
{
	if ((*cmd)->r_io[0] != STDIN_FILENO)
		close((*cmd)->r_io[0]);
	else if ((*cmd)->r_io[1] != STDOUT_FILENO)
		close((*cmd)->r_io[1]);

	*token_lst = (*token_lst)->next;

	if (!*token_lst || ((t_token*)(*token_lst)->content)->token_type == T_PIPE)
		return (write_error_msg("minishell", "parse error near \'>\'", NULL, 1));
	
	//Check for $, expand if so
	(*cmd)->r_io[1] = open(CAST((*token_lst), t_token*)->token, o_flags, 0644);
	if ((*cmd)->r_io[1] < 0)
	{
		write_error_msg("minishell", CAST((*token_lst), t_token*)->token, strerror(errno), 1);
		return (1);
	}
	*token_lst = (*token_lst)->next;
	return (0);
}

//int		parse_redirection(t_cmd **cmd, t_list **token_lst)
int		handle_redirection(t_cmd **cmd, t_list **token_lst)
{
	int	o_flags;

	o_flags = O_CREAT | O_TRUNC | O_RDWR;
	if (CAST((*token_lst), t_token*)->token_type == T_DGREAT)
		o_flags = O_CREAT | O_APPEND | O_RDWR;

	if (*CAST((*token_lst), t_token*)->token == '<')
		return (redirect_input(token_lst, cmd));
	else
		return (redirect_output(token_lst, cmd, o_flags));
	return (0);
}
