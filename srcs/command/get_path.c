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

char	**get_path()
{
	char	**path;
	char	*ptr;

	ptr = ft_getenv(prg->env_lst, "PATH");
	path = ft_split(ptr, ':');
	add_path_slash(path);
	free(ptr);
	return (path);
}