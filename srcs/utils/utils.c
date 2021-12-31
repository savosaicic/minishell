/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/31 09:45:21 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd_name)
{
	if (!ft_strcmp(cmd_name, "echo"))
		return (1);
	else if (!ft_strcmp(cmd_name, "cd"))
		return (1);
	else if (!ft_strcmp(cmd_name, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd_name, "export"))
		return (1);
	else if (!ft_strcmp(cmd_name, "unset"))
		return (1);
	else if (!ft_strcmp(cmd_name, "env"))
		return (1);
	else if (!ft_strcmp(cmd_name, "exit"))
		return (1);
	else if (!ft_strcmp(cmd_name, "env"))
		return (1);
	else if (!ft_strcmp(cmd_name, ":"))
		return (1);
	return (0);
}

void	*xxmalloc(size_t size)
{
	void	*result;

	result = malloc(size);
	if (result == NULL)
		exit(1);
	return (result);
}

void	ft_close(int *fd)
{
	if (*fd > 0)
		close(*fd);
	*fd = -1;
}

int	is_line_empty(char *line)
{
	int	i;

	i = 1;
	while (*line)
	{
		if (!is_space(*line))
			i = 0;
		line++;
	}
	return (i);
}
