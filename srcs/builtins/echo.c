/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboisser <jboisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by jboisser          #+#    #+#             */
/*   Updated: 2022/01/02 09:05:07 by jboisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_nflag(char *s)
{
	if (*s != '-')
		return (false);
	s++;
	if (*s != 'n')
		return (false);
	while (*s && *s == 'n')
		s++;
	if (!*s)
		return (true);
	return (false);
}

int	echo(t_cmd *cmd)
{
	int	newline;
	int	i;

	i = 1;
	newline = true;
	while (cmd->args[i] && is_nflag(cmd->args[i]))
	{
		newline = false;
		i++;
	}
	if (!cmd->args[i])
	{
		if (newline)
			ft_putchar('\n');
		return (0);
	}
	while (cmd->args[i])
	{
		ft_putstr(cmd->args[i]);
		if (cmd->args[i + 1])
			ft_putstr(" ");
		i++;
	}
	if (newline)
		ft_putchar('\n');
	return (0);
}
