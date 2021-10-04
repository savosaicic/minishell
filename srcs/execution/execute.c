#include "minishell.h"

void     execute_builtin(t_prg *prg, t_cmd *cmd)
{
    (void)prg;
	echo(cmd);
}

void		execute_command(t_prg *prg, t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	int		ret;

	pid = fork();
	if (pid == -1)
		exit_failure(prg, NULL, strerror(errno), 1);
	if (!pid)
	{
		dup2(cmd->r_io[0], STDIN_FILENO);
		dup2(cmd->r_io[1], STDOUT_FILENO);
		execve(cmd->path, cmd->args, prg->env);
		exit_failure(prg, cmd, strerror(errno), 127);
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

int execute(t_prg *prg, t_cmd *cmd)
{
    (void)prg;
    int ret;

    if (is_builtin(cmd->args[0]))
    	execute_builtin(prg, cmd);
    else
    	execute_command(prg, cmd);				
    ret = wait_all_pids();
    return (ret);
}