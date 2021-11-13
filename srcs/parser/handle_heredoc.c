#include "minishell.h"

int		handle_heredoc(t_list **token_lst)
{
	int		fds[2];
	char	*line;
	char	*delimiter;

	pipe(fds);
	*token_lst = (*token_lst)->next;
	delimiter = CAST((*token_lst), t_token*)->token;
	line = readline("> ");
	while (ft_strcmp(line, delimiter))
	{
		free(line);
		line = readline("> ");
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
	}
	free(line);
	close(fds[1]);
	return (fds[0]);
}