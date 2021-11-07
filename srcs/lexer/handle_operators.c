#include "minishell.h"

static int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '\"' || c == '\'' || c == ' ');
}

int	handle_quote(char **cmd_buffer, char *str, t_list **token_lst)
{
	unsigned char	quote;
	char			buffer[4096];
	int				i;

	quote = **cmd_buffer;
	(*cmd_buffer)++;
	i = 0;
	while (**cmd_buffer != quote && **cmd_buffer)
		buffer[i++] = *(*cmd_buffer)++;
	if (!**cmd_buffer)
		return (1);
	(*cmd_buffer)++;
	while (!is_operator(**cmd_buffer) && **cmd_buffer)
		buffer[i++] = *(*cmd_buffer)++;
	buffer[i] = '\0';

	if (str)
		ft_lstadd_back(token_lst, ft_lstnew(write_token(ft_strjoin(str, buffer))));
	else
		ft_lstadd_back(token_lst, ft_lstnew(write_token(buffer)));
	return (0);
}

int	handle_pipe_and_redirection(char **cmd_buffer, t_list **token_lst)
{
	char	operator[2];

	operator[0] = **cmd_buffer;
	operator[1] = 0;
	ft_lstadd_back(token_lst, ft_lstnew(write_token(operator)));
	(*cmd_buffer)++;
	return (0);
}
