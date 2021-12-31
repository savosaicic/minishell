/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/31 09:54:09 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_cmd_and_jump_to_next(t_cmd **cmd, int *args_index,
	t_list **token_lst)
{
	if (!cmd || !*cmd)
		return ;
	free(((t_cmd *)(*cmd))->args[0]);
	((t_cmd *)(*cmd))->args[0] = ft_strdup(":");
	if (*args_index == 0)
		*args_index = 1;
	if ((*cmd)->r_io[0] != STDIN_FILENO)
		ft_close(&(*cmd)->r_io[0]);
	if ((*cmd)->r_io[1] != STDOUT_FILENO)
		ft_close(&(*cmd)->r_io[1]);
	(*cmd)->r_io[0] = STDIN_FILENO;
	(*cmd)->r_io[1] = STDOUT_FILENO;
	while (*token_lst && CAST((*token_lst), t_token *)->token_type != T_PIPE)
		*token_lst = (*token_lst)->next;
}

static int	redirect_input(t_list **token_lst, t_cmd **cmd, int *i)
{
	if ((*cmd)->r_io[0] != STDIN_FILENO)
		ft_close(&(*cmd)->r_io[0]);
	*token_lst = (*token_lst)->next;
	(*cmd)->r_io[0] = open(CAST((*token_lst), t_token *)->token, O_RDONLY);
	if ((*cmd)->r_io[0] < 0)
	{
		puterror(CAST((*token_lst), t_token *)->token, strerror(errno), 1);
		if (is_token_in_list(*token_lst, T_PIPE) || !(*cmd)->is_first)
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

static int	redirect_output(t_list **token_lst, t_cmd **cmd, int o_flags,
	int *i)
{
	if ((*cmd)->r_io[1] != STDOUT_FILENO)
		ft_close(&(*cmd)->r_io[1]);
	*token_lst = (*token_lst)->next;
	(*cmd)->r_io[1] = open(CAST((*token_lst), t_token *)->token, o_flags, 0644);
	if ((*cmd)->r_io[1] < 0)
	{
		puterror(CAST((*token_lst), t_token *)->token, strerror(errno), 1);
		if (is_token_in_list(*token_lst, T_PIPE) || !(*cmd)->is_first)
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

int	parse_redirection(t_list **token_lst, t_cmd **cmd, int *i)
{
	if (*CAST((*token_lst), t_token *)->token == '<')
		return (redirect_input(token_lst, cmd, i));
	else
	{
		if (CAST((*token_lst), t_token *)->token_type == T_DGREAT)
			return (redirect_output(token_lst, cmd,
					O_CREAT | O_APPEND | O_RDWR, i));
		else
			return (redirect_output(token_lst, cmd,
					O_CREAT | O_TRUNC | O_RDWR, i));
	}
	return (0);
}
