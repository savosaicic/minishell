/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/30 16:04:25 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_cmd *cmd)
{
	char	buffer[256];

	(void)cmd;
	if (!getcwd(buffer, 256))
		return (puterror(strerror(errno), NULL, 1));
	ft_putstr(buffer);
	ft_putchar_fd('\n', 1);
	return (0);
}

int	cd(t_cmd *cmd, char *home_path)
{
	char	*tmp;

	if (g_prg->child == TRUE)
		return (0);
	if (ft_charlen(cmd->args) > 2)
		return (puterror(NULL, "too many arguments", 1));
	if (!cmd->args[1] || cmd->args[1][0] == '~')
		tmp = home_path;
	else
		tmp = cmd->args[1];
	if (chdir(tmp) == -1)
		return (puterror(cmd->args[1], strerror(errno), 1));
	return (0);
}
