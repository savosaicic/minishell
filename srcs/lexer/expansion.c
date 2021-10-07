#include "minishell.h"

char	*perform_expansion(char **cmd_buffer)
{
	char	buffer[4096];
	char	*expanded_var;
	char	*tmp;
	int		i;

	ft_bzero(buffer, 4096);
	(*cmd_buffer)++;
	i = 0;
	while (**cmd_buffer)
	{
		if (is_space(**cmd_buffer) || **cmd_buffer == '$')
			break;
		buffer[i++] = **cmd_buffer;
		(*cmd_buffer)++;
	}
	tmp = getenv(buffer);
	if (!tmp)
		return (NULL);
	expanded_var = ft_strdup(getenv(buffer));
	return (expanded_var);
}

char	*handle_expansion(char **cmd_buffer)
{
	char	*expanded_var;
	char	*buffer;
	char	*tmp;

	buffer = ft_strdup("");
	while (**cmd_buffer == '$')
	{
		expanded_var = perform_expansion(cmd_buffer);
		tmp = buffer;
		buffer = ft_strjoin(buffer, expanded_var);
		free(tmp);
		free(expanded_var);
	}
	return (buffer);
}
