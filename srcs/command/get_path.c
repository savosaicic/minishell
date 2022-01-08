/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboisser <jboisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by jboisser          #+#    #+#             */
/*   Updated: 2022/01/05 15:53:22 by jboisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_path_slash(char **path)
{
	int		i;

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

	ptr = ft_getenv(g_prg->env_lst, "PATH");
	path = ft_split(ptr, ':');
	add_path_slash(path);
	free(ptr);
	return (path);
}
