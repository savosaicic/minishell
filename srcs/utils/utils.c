#include "minishell.h"

int     is_builtin(char *cmd_name)
{
    if (!ft_strcmp(cmd_name, "echo"))
        return (1);
    else if (!ft_strcmp(cmd_name, "cd"))
        return (1);
    else if (!ft_strcmp(cmd_name, "pwd"))
        return (1);
    else if (!ft_strcmp(cmd_name, "export"))
        return (1);
    else if (!ft_strcmp(cmd_name, "unset"))
        return (1);
    else if (!ft_strcmp(cmd_name, "env"))
        return (1);
    else if (!ft_strcmp(cmd_name, "exit"))
        return (1);
    else if (!ft_strcmp(cmd_name, "env"))
        return (1);
    return (0);
}

int     is_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
        || c == '\v' || c == '\f')
        return (1);
    return (0);
}

void wait_all_pids(t_io	io_struct)
{
	int status;
	int pid_ret;
    // int first;

	pid_ret = 1;
    // first = 0;
    prg->exit_status = 0;
	while (pid_ret > 0)
	{
        // if (first == 0)
        // {
        //     dprintf(2, "first child\n");
        //     restore_and_close_fds(io_struct);
        // }
        // else
        // {

        //     dprintf(2, "second child\n");
        //     restore_and_close_fds2(io_struct);
        // }
		pid_ret = wait(&status);
		if (WIFEXITED(status))
            prg->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
            prg->exit_status = WTERMSIG(status);
        // first++;
	}
}

int	ft_charlen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	is_redirect(char c)
{
	return (c == '<' || c == '>');
}

int	is_pipe(char c)
{
	return (c == '|');
}