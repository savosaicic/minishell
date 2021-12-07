#include "minishell.h"

void	restore_and_close_fds(t_io io_struct)
{
	dup2(io_struct.save_stdin, STDIN_FILENO);
	dup2(io_struct.save_stdout, STDOUT_FILENO);
	ft_close(io_struct.save_stdin);
	ft_close(io_struct.save_stdout);
	ft_close(io_struct.fdin);
	// dprintf(2, "fds %d\n", io_struct.fdout);
	ft_close(io_struct.fdout);
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
	return (io_struct);
}

t_io	set_fd_last_cmd(t_cmd *cmd, t_io io_struct)
{
	if (cmd->r_io[0] != STDIN_FILENO)
	{
		dup2(cmd->r_io[0], STDIN_FILENO);
		ft_close(cmd->r_io[0]);
		ft_close(io_struct.fdin); // change 
	}
	if (cmd->r_io[1] != STDOUT_FILENO)
	{
		io_struct.fdout = cmd->r_io[1];
	}
	else
	{
		io_struct.fdout = dup(io_struct.save_stdout);
	}
	return (io_struct);
}

t_io	set_fds(t_cmd *cmd, t_io io_struct)
{
	pipe(io_struct.fds);
	if (cmd->r_io[0] != STDIN_FILENO)
	{
		dup2(cmd->r_io[0], STDIN_FILENO);
		ft_close(cmd->r_io[0]);
		ft_close(io_struct.fdin); // new ? 
	}
	else
	{
		io_struct.fdin = io_struct.fds[0];
	}
	if (cmd->r_io[1] != STDOUT_FILENO)
	{
		io_struct.fdout = cmd->r_io[1];
		ft_close(io_struct.fds[1]); // change
	}
	else
	{
		io_struct.fdout = io_struct.fds[1];
	}
	return (io_struct);
}