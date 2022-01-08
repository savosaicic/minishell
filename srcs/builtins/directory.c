/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboisser <jboisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by jboisser          #+#    #+#             */
/*   Updated: 2022/01/02 16:32:20 by jboisser         ###   ########.fr       */
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
	DIR		*directory;
	char	*tmp;

	if (ft_charlen(cmd->args) > 2)
		return (puterror("cd", "too many arguments", 1));
	if (!cmd->args[1] || cmd->args[1][0] == '~')
		tmp = home_path;
	else
		tmp = cmd->args[1];
	if (g_prg->child == FALSE)
	{
		if (chdir(tmp) == -1)
			return (puterror(cmd->args[1], strerror(errno), 1));
	}
	else if (g_prg->child == TRUE && cmd->args[1]
		&& ft_strcmp(cmd->args[1], "~") != 0)
	{
		directory = opendir(cmd->args[1]);
		if (!directory)
			return (puterror(cmd->args[1], strerror(errno), 1));
		closedir(directory);
	}
	return (0);
}
