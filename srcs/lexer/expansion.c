/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/30 15:51:17 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lex_expansion(t_list **token_lst, char **cmd_buffer,
	char **buffer)
{
	char	*expander_var;
	char	*tmp;

	expander_var = NULL;
	if (ft_strlen(*buffer))
		expander_var = ft_strdup(*buffer);
	tmp = handle_expansion(g_prg, cmd_buffer, &expander_var, token_lst);
	ft_bzero(*buffer, MAX_TOKEN_SIZE);
	if (ft_strlen(tmp))
		ft_memcpy(*buffer, tmp, ft_strlen(tmp));
	free(tmp);
	free(expander_var);
	return (0);
}

int	lex_quotes(t_list **token_lst, char **cmd_buffer, char **buffer)
{
	char	*tmp;

	if (ft_strlen(*buffer))
		tmp = handle_quote(token_lst, cmd_buffer, *buffer);
	else
		tmp = handle_quote(token_lst, cmd_buffer, NULL);
	ft_bzero(*buffer, MAX_TOKEN_SIZE);
	if (tmp)
		ft_strcat(*buffer, tmp);
	free(tmp);
	return (ft_strlen(*buffer));
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
	(void)g_prg;
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
