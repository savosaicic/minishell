#include "minishell.h"

int		execute_command(t_prg *prg, t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	int		ret;

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
		waitpid(pid, &status, 0);
		ret = 0;
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
		exit(ret);
	}
}