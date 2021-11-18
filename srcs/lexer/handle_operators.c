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

//	while (**cmd_buffer != quote && **cmd_buffer)
//		buffer[i++] = *(*cmd_buffer)++;

	ft_bzero(buffer, 4096);
	while (**cmd_buffer != quote && **cmd_buffer)
	{
		if (**cmd_buffer == '$' && *(*cmd_buffer + 1) && *(*cmd_buffer + 1) != '$' && *(*cmd_buffer + 1) != ' ')
		{

		}

		buffer[i] = **cmd_buffer;
		(*cmd_buffer)++;
		i++;
	}

	if (!**cmd_buffer)
		return (1);

	(*cmd_buffer)++;
	while (!is_operator(**cmd_buffer) && **cmd_buffer)
		buffer[i++] = *(*cmd_buffer)++;
	buffer[i] = '\0';

	printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("\t\"%s\"\n", buffer);
	printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	if (str)
		ft_lstadd_back(token_lst, ft_lstnew(write_token(ft_strjoin(str, buffer))));
	else
		ft_lstadd_back(token_lst, ft_lstnew(write_token(buffer)));
	return (0);
}

int	handle_pipe_and_redirection(char **cmd_buffer, t_list **token_lst)
{
	char	operators[4];
	int		i;

	ft_bzero(operators, 4);
	operators[0] = **cmd_buffer;
	(*cmd_buffer)++;
	i = 1;
	while (**cmd_buffer == operators[0])
	{
		if (i > 2)
			break ;
		operators[i] = **cmd_buffer;
		(*cmd_buffer)++;
		i++;
	}
	while (**cmd_buffer == operators[0])
		(*cmd_buffer)++;
	ft_lstadd_back(token_lst, ft_lstnew(write_token(operators)));
	if (is_pipe(operators[0]) && ft_strlen(operators) > 1)
		return (-1);
	else if (is_redirect(operators[0]) && ft_strlen(operators) > 2)
		return (-1);
	return (1);
}
