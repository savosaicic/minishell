
#include "minishell.h"

int		exec_cmd(t_cmd *cmd)
{
	pid_t	pid;
	int		status;


	pid = fork();
	if (pid == -1)
		exit_failure(NULL, strerror(ernno), 1);
	if (pid > 0)
	{
		execve(cmd->args[0], cmd->args, NULL);
		exit_failture(NULL, strerror(ernoo), 127);
	}
	else
		wait(&status);
	return (0);
}
