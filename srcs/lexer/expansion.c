#include "minishell.h"

int	lex_expansion(t_list **token_lst, char **cmd_buffer,
	char **buffer)
{
	char	*expander_var;

	expander_var = NULL;
	if (ft_strlen(*buffer))
		expander_var = ft_strdup(*buffer);
	handle_expansion(prg, cmd_buffer, &expander_var, token_lst);
	ft_bzero(*buffer, MAX_TOKEN_SIZE);
	free(expander_var);
	return (0);
}

int	lex_quotes(t_list **token_lst, char **cmd_buffer, char **buffer)
{
	if (ft_strlen(*buffer))
		handle_quote(prg, cmd_buffer, *buffer, token_lst);
	else
		handle_quote(prg, cmd_buffer, NULL, token_lst);
	ft_bzero(*buffer, MAX_TOKEN_SIZE);
	return (0);
}

int	lex_operators(t_list **token_lst, char **cmd_buffer,
	char **buffer)
{
	if (ft_strlen(*buffer))
		ft_lstadd_back(token_lst, ft_lstnew(write_token(*buffer)));
	ft_bzero(*buffer, MAX_TOKEN_SIZE);
	if (handle_pipe_and_redirection(cmd_buffer, token_lst) == -1)
	{
		ft_lstclear(token_lst, clear_token_struct);
		exit_failure("parse error near", "TOCHANGE", 1);
	}
	return (0);
}

int	lex_spaces(t_list **token_lst, char **cmd_buffer, char **buffer)
{
	(void)prg;
	while (**cmd_buffer == ' ')
		(*cmd_buffer)++;
	if (ft_strlen(*buffer))
		ft_lstadd_back(token_lst, ft_lstnew(write_token(*buffer)));
	ft_bzero(*buffer, MAX_TOKEN_SIZE);
	return (0);
}

int	lex_chars(int i, char **cmd_buffer, char **buffer)
{
	(*buffer)[i] = **cmd_buffer;
	(*cmd_buffer)++;
	return (i + 1);
}
