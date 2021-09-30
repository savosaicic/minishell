#include "minishell.h"

static void	add_path_slash(char **path)
{
	int		i;
	// char	*tmp;

	i = 0;
	while (path[i])
	{
		// tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		i++;
		// free(tmp);
	}
}

char	**get_path(char **envp)
{
	char	**path;
	char	*ptr;

	while (envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
		{
			ptr = ft_memchr(*envp, '=', 5);
			path = ft_split(++ptr, ':');
			break ;
		}
		envp++;
	}
	if (envp == NULL)
		return (NULL);
	add_path_slash(path);
	return (path);
}