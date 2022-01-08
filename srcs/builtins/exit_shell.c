/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboisser <jboisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by jboisser          #+#    #+#             */
/*   Updated: 2021/12/14 09:51:41 by jboisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_shell(t_cmd *cmd, char *exit_str)
{
	pid_t	pid;

	pid = 0;
	if (!exit_str)
		pid = fork();
	if (!pid)
	{
		if (ft_charlen(cmd->args) > 2)
		{
			ft_putstr_fd(exit_str, 2);
			return (puterror("exit", "too many arguments", 1));
		}
		else if (cmd->args[1] && !ft_str_isdigit(cmd->args[1]))
		{
			ft_putstr_fd(exit_str, 2);
			exit_failure("exit", "numeric argument required", 2);
		}
		else if (cmd->args[1])
			exit_success(ft_atoi(cmd->args[1]), exit_str != NULL);
		else
			exit_success(0, exit_str != NULL);
	}
	if (!exit_str)
		return (wait_pid(pid));
	return (0);
}
