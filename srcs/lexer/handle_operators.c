#include "minishell.h"

int	handle_quote(char **cmd_buffer, t_list **token_lst)
{
	unsigned char	quote;
	char			buffer[4096];
	int				i;

	quote = **cmd_buffer;
	(*cmd_buffer)++;
	i = 0;
	while (**cmd_buffer != quote && **cmd_buffer)
	{
		buffer[i++] = *(*cmd_buffer)++;
	}
	if (!**cmd_buffer)
		return (1);
	buffer[i] = '\0';
	(*cmd_buffer)++;
	ft_lstadd_back(token_lst, ft_lstnew(init_token_struct(buffer)));
	return (0);
}

int	handle_pipe_and_redirection(char **cmd_buffer, t_list **token_lst)
{
	char	operator[2];

	operator[0] = **cmd_buffer;
	operator[1] = 0;
	ft_lstadd_back(token_lst, ft_lstnew(init_token_struct(operator)));
	(*cmd_buffer)++;
	return (0);
}
