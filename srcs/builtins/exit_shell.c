/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/14 09:51:41 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_shell(t_cmd *cmd)
{
	if (ft_charlen(cmd->args) > 2)
	{
		ft_putstr_fd("exit\n", 2);
		return (puterror("exit", "too many arguments", 1));
	}
	else if (cmd->args[1] && !ft_str_isdigit(cmd->args[1]))
	{
		ft_putstr_fd("exit\n", 2);
		exit_failure("exit", "numeric argument required", 2);
	}
	else if (cmd->args[1])
		exit_success(ft_atoi(cmd->args[1]), TRUE);
	else
		exit_success(0, TRUE);
	return (1);
}
