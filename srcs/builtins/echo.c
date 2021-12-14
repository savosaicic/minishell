/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/14 09:08:30 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_cmd *cmd)
{
	int	option;
	int	i;

	if (!cmd->args[1])
	{
		ft_putchar('\n');
		return (0);
	}
	option = 0;
	i = 1;
	while (!ft_strcmp(cmd->args[i], "-n") || is_space(cmd->args[i][0]))
	{
		option = 1;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr(cmd->args[i]);
		if (cmd->args[i + 1])
			ft_putstr(" ");
		i++;
	}
	if (!option)
		ft_putchar('\n');
	return (0);
}
