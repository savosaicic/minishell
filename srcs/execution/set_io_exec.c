/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_io_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/14 10:12:45 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_io	set_file_descriptors(t_list **cmd_lst, t_io io_struct, int cmds_len,
		int *is_first)
{
	if (cmds_len == 1)
		io_struct = set_fd_last_cmd(cmd_lst, io_struct, is_first);
	else
		io_struct = set_fds(cmd_lst, io_struct, is_first);
	return (io_struct);
}

t_io	replace_cmd_io_and_exec(t_list **cmd_lst, t_io io_struct)
{
	int	ret;

	dup2(((t_cmd *)(*cmd_lst)->content)->fdin, STDIN_FILENO);
	dup2(((t_cmd *)(*cmd_lst)->content)->fdout, STDOUT_FILENO);
	close(((t_cmd *)(*cmd_lst)->content)->fdout);
	close(((t_cmd *)(*cmd_lst)->content)->fdin);
	if (!is_builtin(((t_cmd *)(*cmd_lst)->content)->args[0])
		|| (ft_strcmp(((t_cmd *)(*cmd_lst)->content)->args[0], "exit") == 0
		&& g_prg->child))
		close(io_struct.close_in_child);
	((t_cmd *)(*cmd_lst)->content)->path
		= write_command(((t_cmd *)(*cmd_lst)->content)->args);
	ret = execute((*cmd_lst)->content);
	if (!is_builtin(((t_cmd *)(*cmd_lst)->content)->args[0])
		|| (ft_strcmp(((t_cmd *)(*cmd_lst)->content)->args[0], "exit") == 0
		&& g_prg->child))
		exit_success(ret, FALSE);
	else
	{
		dup2(io_struct.save_stdin, STDIN_FILENO);
		dup2(io_struct.save_stdout, STDOUT_FILENO);
	}
	return (io_struct);
}

t_io	set_and_execute_command(t_list **cmd_lst, t_io io_struct, int cmds_len,
		int *is_first)
{
	g_prg->pid = 0;
	io_struct = set_file_descriptors(cmd_lst, io_struct, cmds_len, is_first);
	if (ft_strchr(rl_line_buffer, '|')) //May be done before ?
		g_prg->child = TRUE;
	if (!is_builtin(((t_cmd *)(*cmd_lst)->content)->args[0])
		|| (ft_strcmp(((t_cmd *)(*cmd_lst)->content)->args[0], "exit") == 0
		&& g_prg->child))
	{
		g_prg->child = TRUE;
		g_prg->pid = fork();
	}
	if (!g_prg->pid)
		io_struct = replace_cmd_io_and_exec(cmd_lst, io_struct);
	else
	{
		close(io_struct.close_in_parent);
		close(((t_cmd *)(*cmd_lst)->content)->fdout);
		close(((t_cmd *)(*cmd_lst)->content)->fdin);
	}
	return (io_struct);
}
