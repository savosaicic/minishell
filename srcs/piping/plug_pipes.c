/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plug_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/31 09:48:38 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_io	assign_fd(t_io io_struct)
{
	int	i;

	io_struct.next_fdin = io_struct.fds[0];
	io_struct.close_in_child = io_struct.fds[0];
	io_struct.close_in_parent = io_struct.fds[1];
	i = 0;
	while (io_struct.last_close[i] != 0)
		i++;
	io_struct.last_close[i] = io_struct.fds[0];
	return (io_struct);
}

void	restore_and_close_fds(t_io io_struct)
{
	int	i;

	dup2(io_struct.save_stdin, STDIN_FILENO);
	dup2(io_struct.save_stdout, STDOUT_FILENO);
	ft_close(&io_struct.save_stdin);
	ft_close(&io_struct. save_stdout);
	ft_close(&io_struct.fdin);
	ft_close(&io_struct.fdout);
	ft_close(&io_struct.fds[0]);
	ft_close(&io_struct.fds[1]);
	i = 0;
	while (io_struct.last_close[i] != 0)
		ft_close(&io_struct.last_close[i++]);
}

t_io	init_io_struct(void)
{
	t_io	io_struct;

	io_struct.save_stdin = dup(STDIN_FILENO);
	io_struct.save_stdout = dup(STDOUT_FILENO);
	io_struct.fdin = dup(STDIN_FILENO);
	io_struct.fdout = -1;
	io_struct.fds[0] = -1;
	io_struct.fds[1] = -1;
	ft_bzero(&io_struct.last_close[0], sizeof(int) * MAX_PIPE);
	return (io_struct);
}

t_io	set_fd_last_cmd(t_list **cmd_lst, t_io io_struct, int *is_first_cmd)
{
	if (((t_cmd *)(*cmd_lst)->content)->r_io[0] != STDIN_FILENO)
		((t_cmd *)(*cmd_lst)->content)->fdin
			= ((t_cmd *)(*cmd_lst)->content)->r_io[0];
	else if (*is_first_cmd == 1)
		((t_cmd *)(*cmd_lst)->content)->fdin = io_struct.fdin;
	else
		((t_cmd *)(*cmd_lst)->content)->fdin = io_struct.next_fdin;
	if (((t_cmd *)(*cmd_lst)->content)->r_io[1] != STDOUT_FILENO)
	{
		((t_cmd *)(*cmd_lst)->content)->fdout
			= ((t_cmd *)(*cmd_lst)->content)->r_io[1];
		ft_close(&io_struct.fds[1]);
	}
	else
		((t_cmd *)(*cmd_lst)->content)->fdout = dup(io_struct.save_stdout);
	io_struct.close_in_child = -1;
	io_struct.close_in_parent = io_struct.fds[0];
	return (io_struct);
}

t_io	set_fds(t_list **cmd_lst, t_io io_struct, int *is_first_cmd)
{
	pipe(io_struct.fds);
	if (((t_cmd *)(*cmd_lst)->content)->r_io[0] != STDIN_FILENO)
		((t_cmd *)(*cmd_lst)->content)->fdin
			= ((t_cmd *)(*cmd_lst)->content)->r_io[0];
	else if (*is_first_cmd == 1)
		((t_cmd *)(*cmd_lst)->content)->fdin = io_struct.fdin;
	else
		((t_cmd *)(*cmd_lst)->content)->fdin = io_struct.next_fdin;
	if (((t_cmd *)(*cmd_lst)->content)->r_io[1] != STDOUT_FILENO)
	{
		((t_cmd *)(*cmd_lst)->content)->fdout
			= ((t_cmd *)(*cmd_lst)->content)->r_io[1];
		ft_close(&io_struct.fds[1]);
		//////////////////////////////
		io_struct.fds[1] = -1;
	}
	else
		((t_cmd *)(*cmd_lst)->content)->fdout = io_struct.fds[1];
	io_struct = assign_fd(io_struct);
	*is_first_cmd = 0;
	return (io_struct);
}
