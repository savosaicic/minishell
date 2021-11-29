#include "minishell.h"

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
