/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/14 10:12:45 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_cmd *cmd)
{
	int	ret;

	ret = 1;
	if (!ft_strcmp(cmd->args[0], "echo"))
		ret = echo(cmd);
	else if (!ft_strcmp(cmd->args[0], "export"))
		ret = export(cmd, g_prg->env_lst);
	else if (!ft_strcmp(cmd->args[0], "unset"))
		ret = unset(cmd, g_prg->env_lst);
	else if (!ft_strcmp(cmd->args[0], "env"))
		ret = print_env(g_prg->env_lst, "");
	else if (!ft_strcmp(cmd->args[0], "pwd"))
		ret = pwd(cmd);
	else if (!ft_strcmp(cmd->args[0], "cd"))
		ret = cd(cmd, g_prg->home_path);
	else if (!ft_strcmp(cmd->args[0], "exit") && g_prg->cmds_len > 1)
		ret = exit_shell(cmd, NULL);
	else if (!ft_strcmp(cmd->args[0], "exit"))
		ret = exit_shell(cmd, "exit\n");
	else if (!ft_strcmp(cmd->args[0], ":"))
		ret = do_nothing();
	return (ret);
}

int	execute_command(t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		if (!cmd->path)
			return (puterror(cmd->args[0], "command not found", 127));
		execve(cmd->path, cmd->args, g_prg->env);
		exit(puterror(cmd->args[0], strerror(errno), 1));
	}
	return (wait_pid(pid));
}

int	execute(t_cmd *cmd)
{
	if (is_builtin(cmd->args[0]))
		g_prg->exit_status = execute_builtin(cmd);
	else
		g_prg->exit_status = execute_command(cmd);
	return (g_prg->exit_status);
}
