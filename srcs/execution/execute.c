#include "minishell.h"

void execute_builtin(t_prg *prg, t_cmd *cmd)
{
	(void)prg;
	if (!ft_strcmp(cmd->args[0], "echo"))
		echo(cmd);
	else if (!ft_strcmp(cmd->args[0], "export"))
		export(cmd, prg->env_lst);
	else if (!ft_strcmp(cmd->args[0], "env"))
		env(prg->env_lst);
}

void execute_command(t_prg *prg, t_cmd *cmd)
{
	execve(cmd->path, cmd->args, prg->env);
	exit_failure(prg, cmd, strerror(errno), 127);
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