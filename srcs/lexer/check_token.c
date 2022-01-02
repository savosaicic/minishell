/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 10:32:27 by sasaicic          #+#    #+#             */
/*   Updated: 2022/01/02 13:22:04 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	syntax_error(t_token *unexpected_token)
{
	bool	newline;
	char	buffer[64];

	newline = false;
	if (!unexpected_token)
		newline = true;
	ft_bzero(&buffer, 64);
	ft_strcat(buffer, "minishell: ");
	ft_strcat(buffer, "syntax error near unexpected token `");
	if (!newline)
		ft_strcat(buffer, (char *)unexpected_token->token);
	else
		ft_strcat(buffer, "newline");
	buffer[ft_strlen(buffer)] = '\'';
	buffer[ft_strlen(buffer)] = '\n';
	ft_putstr_fd(buffer, STDERR_FILENO);
	return (-1);
}

static bool	check_pipe(t_token *current, t_token *next, bool is_first)
{
	if (ft_strlen(current->token) > 1 || !next || is_first)
		return (false);
	else if (next->token_type == T_PIPE)
		return (false);
	return (true);
}

static bool	check_redirect(t_token *current, t_token *next)
{
	if (ft_strlen(current->token) > 2 || !next)
		return (false);
	else if (next->token_type == T_REDIRECT || next->token_type == T_DGREAT)
		return (false);
	else if (next->token_type == T_PIPE || next->token_type == T_DLESS)
		return (false);
	return (true);
}

int	check_token(t_list *token_lst)
{
	t_token	*current;
	t_token	*next;
	bool	is_first;

	is_first = true;
	while (token_lst)
	{
		current = (t_token *)token_lst->content;
		if (!token_lst->next)
			next = NULL;
		else
			next = (t_token *)(token_lst->next)->content;
		if (current->token_type == T_PIPE
			&& !check_pipe(current, next, is_first))
			return (syntax_error(next));
		else if (is_redirect(*current->token) && !check_redirect(current, next))
			return (syntax_error(next));
		token_lst = token_lst->next;
		is_first = false;
	}
	return (0);
}
