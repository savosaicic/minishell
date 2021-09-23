#include "minishell.h"

int		exec_cmd(t_prg *prg, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exit_failure(prg, cmd, strerror(errno), 127);
	if (!pid)
	{
		execve(cmd->path, cmd->args, prg->env);
		exit_failure(prg, cmd, strerror(errno), 127);
	}
	else
	{
		wait(&status);
	}
	return (0);
}
