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

static void	split_buffer_and_add_back(char *buffer, t_list **token_lst)
{
	char	**res;
	int		i;

	res = ft_split(buffer, ' ');
	if (!res)
		return ;
	i = 0;
	while (res[i])
	{
		ft_lstadd_back(token_lst, ft_lstnew(write_token(res[i])));
		i++;
	}
	free_tab(res);
}

char	*handle_expansion(char **cmd_buffer, char *save, t_list **token_lst)
{
	char	*expanded_var;
	char	*buffer;
	char	*tmp;

	if (save)
	{
		buffer = ft_strdup(save);
		free(save);
	}
	else
		buffer = ft_strdup("");
	while (**cmd_buffer == '$')
	{
		expanded_var = perform_expansion(cmd_buffer);
		tmp = buffer;
		buffer = ft_strjoin(buffer, expanded_var);
		free(tmp);
		free(expanded_var);
	}
	split_buffer_and_add_back(buffer, token_lst);
	return (buffer);
}
