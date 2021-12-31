/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:43:59 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/31 15:24:47 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_prg	*g_prg;

t_prg	*init_shell(char **env)
{
	g_prg = malloc(sizeof(*g_prg));
	if (!g_prg)
		exit_failure(NULL, "insufficient memory", 1);
	if (!*env)
	{
		g_prg->env = xxmalloc(sizeof(*g_prg->env));
		*g_prg->env = NULL;
	}
	else
		g_prg->env = env;
	g_prg->env_lst = init_env();
	g_prg->pwd = ft_getenv(g_prg->env_lst, "PWD");
	g_prg->home_path = ft_getenv(g_prg->env_lst, "HOME");
	g_prg->cmd_buffer = NULL;
	g_prg->exit_status = 0;
	g_prg->in_heredoc = false;
	g_prg->save_stdin = dup(STDIN_FILENO);
	g_prg->sig_int = 0;
	return (g_prg);
}

int	check_token(t_list *token_lst)
{
	int	is_first;

	is_first = 1;
	while (token_lst)
	{
		if (((t_token *)token_lst->content)->token_type == T_PIPE
			&& (ft_strlen(((t_token *)token_lst->content)->token) > 1
				|| !token_lst->next || is_first))
			return (puterror(NULL,
					"syntax error near unexpected token `|\'", -1));
		else if (((t_token *)token_lst->content)->token_type == T_REDIRECT
			&& (ft_strlen(((t_token *)token_lst->content)->token) > 2
				|| !token_lst->next))
			return (puterror("syntax error near unexpected token",
					((t_token *)token_lst->content)->token, -1));
		token_lst = token_lst->next;
		is_first = 0;
	}
	return (0);
}

t_list	*get_command_lst(char *cmd_buffer)
{
	t_list	*token_lst;
	t_list	*cmd_lst;

	cmd_lst = NULL;
	add_history(cmd_buffer);
	if (check_quote_and_forbiden_char(cmd_buffer) > 0)
		return (NULL);
	token_lst = get_token(cmd_buffer);
	if (token_lst == NULL)
		return (NULL);
	else if (check_token(token_lst) != -1)
		cmd_lst = parse_tokens(token_lst);
	ft_lstclear(&token_lst, clear_token_struct);
	if (!cmd_lst)
		ft_lstclear(&cmd_lst, clear_cmd_struct);
	return (cmd_lst);
}

void	execution_manager(t_list *cmd_lst)
{
	t_io	io_struct;
	int		cmds_len;
	int		is_first;

	cmds_len = ft_lstsize(cmd_lst);
	io_struct = init_io_struct();
	g_prg->cmd_lst = cmd_lst;
	g_prg->cmds_len = cmds_len;
	is_first = 1;
	while (cmds_len)
	{
		io_struct = set_and_execute_command(&cmd_lst, io_struct, cmds_len,
				&is_first);
		cmd_lst = cmd_lst->next;
		cmds_len--;
	}
	restore_and_close_fds(io_struct);
	if (g_prg->child)
		wait_all_pids();
}

int	main(int ac __attribute__((unused)), char **av __attribute__((unused)),
	char **env)
{
	t_list	*cmd_lst;

	init_shell(env);
	watch_signals();
	g_prg->cmd_buffer = NULL;
	while (1)
	{
		cmd_lst = NULL;
		g_prg->child = FALSE;
		free(g_prg->cmd_buffer);
		g_prg->cmd_buffer = NULL;
		g_prg->cmd_buffer = readline("$> ");
		if (!g_prg->cmd_buffer)
			ft_exit(0, TRUE);
		else if (!is_line_empty(g_prg->cmd_buffer))
			cmd_lst = get_command_lst(g_prg->cmd_buffer);
		if (cmd_lst)
			execution_manager(cmd_lst);
		ft_lstclear(&cmd_lst, clear_cmd_struct);
	}
	return (0);
}
