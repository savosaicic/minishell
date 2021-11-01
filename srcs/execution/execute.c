#include "minishell.h"

int     execute_builtin(t_prg *prg, t_cmd *cmd)
{
    int ret;

    (void)prg;
    ret = 1;
    if (!ft_strcmp(cmd->args[0], "echo"))
        ret = echo(cmd);
    else if (!ft_strcmp(cmd->args[0], "export"))
        ret = export(cmd, prg->env_lst);
    else if (!ft_strcmp(cmd->args[0], "unset"))
        ret = unset(cmd, prg->env_lst);
    else if (!ft_strcmp(cmd->args[0], "env"))
        ret = print_env(prg->env_lst, "");
    else if (!ft_strcmp(cmd->args[0], "pwd"))
        ret = pwd(cmd);
    else if (!ft_strcmp(cmd->args[0], "cd"))
        ret = cd(cmd, prg->home_path);
    else if (!ft_strcmp(cmd->args[0], "exit"))
        ret = exit_shell(prg, cmd);
    return (ret);
}

int execute_command(t_prg *prg, t_cmd *cmd)
{
    pid_t pid;
    int ret;
    int status;

    ret = 0;
    pid = fork();
    if (!pid)
    {
    	if (!cmd->path)
        	return (write_error_msg("minishell", cmd->args[0], "command not found", 127));
	    execve(cmd->path, cmd->args, prg->env);
        exit(write_error_msg("minishell", cmd->args[0], strerror(errno), 1));
    }
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
		prg->last_exit_status = WEXITSTATUS(status);
	return(ret);
}

int execute(t_prg *prg, t_cmd *cmd)
{
    int ret;

    ret = 1;
    if (is_builtin(cmd->args[0]))
        ret = execute_builtin(prg, cmd);
    else
        ret = execute_command(prg, cmd);
    return (ret);
}
