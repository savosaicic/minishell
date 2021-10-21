#include "minishell.h"

t_io	*init_io_struct(void)
{
	t_io	*io_struct;

	io_struct = malloc(sizeof(t_io *));
	if (!io_struct)
		return (NULL);
	io_struct->save_stdin = dup(STDIN_FILENO);
	io_struct->save_stdout = dup(STDOUT_FILENO);
	io_struct->fdin = dup(STDIN_FILENO);
	return (io_struct);
}

t_io	*set_fd_last_cmd(t_cmd *cmd, t_io *io_struct)
{
	if (cmd->r_io[1] != STDOUT_FILENO)
		io_struct->fdout = cmd->r_io[1];
	else
		io_struct->fdout = dup(io_struct->save_stdout);
	return (io_struct);
}

t_io	*set_fds(t_cmd *cmd, t_io *io_struct)
{
	pipe(io_struct->fds);
	if (cmd->r_io[0] != 0)
	{
		io_struct->fdin = cmd->r_io[0];
		close(io_struct->fds[0]);
	}
	else
		io_struct->fdin = io_struct->fds[0];
	if (cmd->r_io[1] != 1)
	{
		io_struct->fdout = cmd->r_io[1];
		close(io_struct->fds[1]);
	}
	else
		io_struct->fdout = io_struct->fds[1];
	return (io_struct);
}