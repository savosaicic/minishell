#include "minishell.h"

void	parse_heredoc(t_list **token_lst, t_cmd **cmd)
{
	int i;
	
	i = 0;
	if (handle_heredoc(token_lst, cmd) > 0)
	{
		while ((*cmd)->args[i])
		{
			free((*cmd)->args[i] = NULL);
			(*cmd)->args[i++] = NULL;
		}
		while ( *token_lst && ((t_token*)(*token_lst)->content)->token_type == T_PIPE)
			*token_lst = (*token_lst)->next;
	}
}