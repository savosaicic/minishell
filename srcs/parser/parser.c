/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2022/01/01 16:26:04 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd_struct(int args_num, bool is_first)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->path = NULL;
	cmd->args = (char **)malloc(sizeof(char *) * (args_num + 1));
	if (!cmd->args)
		return (NULL);
	i = 0;
	while (i < args_num + 1)
		cmd->args[i++] = NULL;
	cmd->r_io[0] = STDIN_FILENO;
	cmd->r_io[1] = STDOUT_FILENO;
	if (is_first == true)
		cmd->is_first = true;
	else
		cmd->is_first = false;
	return (cmd);
}

static int	is_redirect_token(t_ttype token_type)
{
	if (token_type == T_REDIRECT || token_type == T_DGREAT)
		return (1);
	return (0);
}

static void	*heredoc_sigint(t_list **cmd_lst)
{
	dup2(g_prg->save_stdin, STDIN_FILENO);
	ft_lstclear(cmd_lst, clear_cmd_struct);
	g_prg->sig_int = false;
	rl_replace_line("", 0);
	return (NULL);
}

t_list	*parse_tokens(t_list *token_lst)
{
	t_list	*cmd_lst;
	t_cmd	*cmd;
	int		i;

	cmd = init_cmd_struct(ft_lstsize(token_lst), true);
	if (!cmd)
		return (NULL);
	i = 0;
	cmd_lst = NULL;
	while (token_lst)
	{
		if (((t_token *)(token_lst)->content)->token_type == T_DLESS)
			parse_heredoc(&token_lst, &cmd);
		else if (is_redirect_token(((t_token *)token_lst->content)->token_type))
			parse_redirection(&token_lst, &cmd, &i);
		else if (((t_token *)token_lst->content)->token_type == T_PIPE)
			parse_pipe(&token_lst, &cmd, &cmd_lst, &i);
		else
			parse_argument(&token_lst, &cmd, &i);
		if (g_prg->sig_int)
			return (heredoc_sigint(&cmd_lst));
	}
	if (cmd && cmd->args[0])
		add_last_cmd(&cmd, &cmd_lst, i);
	return (cmd_lst);
}
