#include "minishell.h"

static int	redirect_input(t_list *token_lst, t_cmd **cmd)
{
	// from '<' to next token :
	token_lst = token_lst->next;

	//Should be the name of the file
	if (!token_lst)
		return (write_error_msg("minishell", "parse error near \'<\'", NULL));
	
	(*cmd)->r_io[0] = open(CAST(token_lst, t_token*)->token, O_RDONLY);
	if ((*cmd)->r_io[0] < 0)
		return (write_error_msg("minishell", CAST(token_lst, t_token*)->token, strerror(errno)));
	return (0);
}

void	parse_redirection(t_cmd *cmd, t_list **token_lst)
{
	if (*CAST((*token_lst), t_token*)->token == '<')
	{
		if (redirect_input(token_lst, &cmd))
			exit_failure(NULL, NULL, "TEST", 127);

	}
	else
		redirect_output();

}