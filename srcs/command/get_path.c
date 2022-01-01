/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2022/01/01 12:32:06 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_path_slash(char **path)
{
	char	*tmp;
	int		i;

	if (!path)
		return ;
	i = 0;
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free(tmp);
		i++;
	}
}

char	**get_path(void)
{
	char	**path;
	char	*ptr;

	ptr = ft_getenv(g_prg->env_lst, "PATH");
	path = ft_split_savo(ptr, ':');
	add_path_slash(path);
	free(ptr);
	return (path);
}
