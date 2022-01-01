/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2022/01/01 16:17:41 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_eof_delimiter(char *line, char *delimiter)
{
	if (line)
		return (0);
	write(2, "warning: here-document delimited by end-of-file (wanted `", 58);
	write(2, delimiter, ft_strlen(delimiter));
	write(2, "')\n", 3);
	return (1);
}

static int	redirect_heredoc(t_list **token_lst, t_cmd **cmd, int pipe_fd)
{
	if ((*cmd)->r_io[0] != STDIN_FILENO)
		ft_close(&(*cmd)->r_io[0]);
	else if ((*cmd)->r_io[1] != STDOUT_FILENO)
		ft_close(&(*cmd)->r_io[1]);
	(*cmd)->r_io[0] = dup(pipe_fd);
	*token_lst = (*token_lst)->next;
	ft_close(&pipe_fd);
	return (0);
}

static int	sig_int_heredoc(char *line, int fds[2])
{
	free(line);
	ft_close(&fds[1]);
	ft_close(&fds[0]);
	return (0);
}

int	handle_heredoc(t_list **token_lst, t_cmd **cmd)
{
	int		fds[2];
	char	*line;
	char	*delimiter;

	pipe(fds);
	*token_lst = (*token_lst)->next;
	if (!*token_lst || ((t_token *)(*token_lst)->content)->token_type == T_PIPE)
		return (puterror(NULL,
				"syntax error near unexpected token `newline\'", 1));
	delimiter = ((t_token *)(*token_lst)->content)->token;
	while (1)
	{
		line = readline("> ");
		if (g_prg->sig_int)
			return (sig_int_heredoc(line, fds));
		if (is_eof_delimiter(line, delimiter) || !ft_strcmp(line, delimiter))
			break ;
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		free(line);
	}
	free(line);
	ft_close(&fds[1]);
	return (redirect_heredoc(token_lst, cmd, fds[0]));
}
