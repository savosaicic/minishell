#include "minishell.h"

void	restore_and_close_fds(t_io io_struct)
{
	dup2(io_struct.save_stdin, STDIN_FILENO);
	dup2(io_struct.save_stdout, STDOUT_FILENO);
	close(io_struct.save_stdin);
	close(io_struct. save_stdout);
	close(io_struct.fdin);
	close(io_struct.fdout);
	close(io_struct.fds[0]);
	close(io_struct.fds[1]);

	for (int i = 0; io_struct.last_close[i] != 0; i++)
		close(io_struct.last_close[i]);
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

	ft_bzero(&io_struct.last_close[0], sizeof(int) * 64);
	return (io_struct);
}

t_io	set_fd_last_cmd(t_list **cmd_lst, t_io io_struct, int *is_first_cmd)
{
	if (*is_first_cmd == 1)
		((t_cmd *)(*cmd_lst)->content)->fdin = io_struct.fdin;

	((t_cmd *)(*cmd_lst)->content)->fdout = dup(io_struct.save_stdout);
	((t_cmd *)(*cmd_lst)->content)->fdin = io_struct.next_fdin;


	io_struct.close_in_child = -1;
	io_struct.close_in_parent = io_struct.fds[0];

	return (io_struct);
}

t_io	set_fds(t_list **cmd_lst, t_io io_struct, int *is_first_cmd)
{
	pipe(io_struct.fds);

	if (*is_first_cmd == 1)
	{
		((t_cmd *)(*cmd_lst)->content)->fdin = io_struct.fdin;
		*is_first_cmd = 0;
	}
	else
		((t_cmd *)(*cmd_lst)->content)->fdin = io_struct.next_fdin;

	((t_cmd *)(*cmd_lst)->content)->fdout = io_struct.fds[1];


	io_struct.next_fdin = io_struct.fds[0];

	io_struct.close_in_child = io_struct.fds[0];
	io_struct.close_in_parent = io_struct.fds[1];

	int i = 0;
	while (io_struct.last_close[i] != 0)
		i++;
	io_struct.last_close[i] = io_struct.fds[0];

	return (io_struct);
}
