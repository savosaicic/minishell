/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/14 09:50:46 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_path_slash(char **path)
{
	int	i;

	if (!path)
		return ;
	i = 0;
	while (path[i])
	{
		path[i] = ft_memjoin(path[i], "/");
		i++;
	}
}

char	**get_path(void)
{
	char	**path;
	char	*ptr;

	ptr = ft_getenv(prg->env_lst, "PATH");
	path = ft_split(ptr, ':');
	add_path_slash(path);
	free(ptr);
	return (path);
}
