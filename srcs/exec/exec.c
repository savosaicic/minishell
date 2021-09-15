#include "minishell.h"

int		exec_cmd(t_prg *prg, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exit_failure(NULL, strerror(errno), 1);
	if (!pid)
	{
		execve(cmd->path, cmd->args, prg->env);
		exit_failure(NULL, strerror(errno), 127);
	}
	else
	{
		wait(&status);
	}
	return (0);
}
