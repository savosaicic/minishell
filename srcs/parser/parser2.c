#include "minishell.h"

char	*search_in_tab(char **env, char *var)
{
	int		i;
	int		var_len;

	i = 0;
	var_len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, var_len) == 0)
			break ;
		i++;
	}
	return (env[i]);
}
