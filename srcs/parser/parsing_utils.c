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
		while (*token_lst && ((t_token *)(*token_lst)->content)->token_type == T_PIPE)
			*token_lst = (*token_lst)->next;
	}
}

void	parse_redirection(t_list **token_lst, t_cmd **cmd)
{
	if (handle_redirection(cmd, token_lst) > 0)
	{
		int j = 0;
		while ((*cmd)->args[j])
		{
			free((*cmd)->args[j] = NULL);
			(*cmd)->args[j++] = NULL;
		}
		while (*token_lst && ((t_token *)(*token_lst)->content)->token_type != T_PIPE)
			*token_lst = (*token_lst)->next;
	}
}

void	parse_pipe(t_list **token_lst, t_cmd **cmd, t_list **cmd_lst, int *i)
{
	(*cmd)->args[*i] = NULL;
	ft_lstadd_back(cmd_lst, ft_lstnew((void *)(*cmd)));
	*cmd = init_cmd_struct(ft_lstsize(*token_lst));
	*i = 0;
	*token_lst = (*token_lst)->next;
}

void	parse_argument(t_list **token_lst, t_cmd **cmd, int *i)
{
	if ((CAST((*token_lst), t_token *)->token_type == T_ASSIGN && *i >= 1) || (CAST((*token_lst), t_token *)->token_type != T_ASSIGN))
	{
		(*cmd)->args[*i] = ft_strdup(((t_token *)(*token_lst)->content)->token);
		*i = *i + 1;
	}
	*token_lst = (*token_lst)->next;
}