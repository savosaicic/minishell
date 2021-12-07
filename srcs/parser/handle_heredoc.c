#include "minishell.h"

static int	redirect_heredoc(t_list **token_lst, t_cmd **cmd, int pipe_fd)
{
	if ((*cmd)->r_io[0] != STDIN_FILENO)
		ft_close((*cmd)->r_io[0]);
	else if ((*cmd)->r_io[1] != STDOUT_FILENO)
		ft_close((*cmd)->r_io[1]);

	//Check for $, expand if so
	(*cmd)->r_io[0] = dup(pipe_fd);
	*token_lst = (*token_lst)->next;
	ft_close(pipe_fd);
	return (0);
}

int		handle_heredoc(t_list **token_lst, t_cmd **cmd)
{
	int		fds[2];
	char	*line;
	char	*delimiter;

	pipe(fds);
	*token_lst = (*token_lst)->next;
	if (!*token_lst || ((t_token*)(*token_lst)->content)->token_type == T_PIPE)
		return (puterror(NULL, "syntax error near unexpected token `newline\'", 1));
	delimiter = CAST((*token_lst), t_token*)->token;
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		free(line);
	}
	free(line);
	ft_close(fds[1]);
	return (redirect_heredoc(token_lst, cmd, fds[0]));
}