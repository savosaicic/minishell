/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/15 14:51:54 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ttype	get_token_type(char *token)
{
	if (ft_onlychr(token, '|'))
		return (T_PIPE);
	else if (!ft_strcmp(token, ">>"))
		return (T_DGREAT);
	else if (!ft_strcmp(token, "<<"))
		return (T_DLESS);
	else if (ft_onlychr(token, '<') || ft_onlychr(token, '>'))
		return (T_REDIRECT);
	else if (!ft_strcmp(token, "<") || !ft_strcmp(token, ">"))
		return (T_REDIRECT);
	else if (ft_strchr(token, '='))
		return (T_ASSIGN);
	else
		return (T_WORD);
}

t_token	*write_token(char *token)
{
	t_token	*token_struct;

	token_struct = malloc(sizeof(*token_struct));
	if (!token_struct)
		return (NULL);
	token_struct->token = ft_strdup(token);
	if (!token_struct->token)
		return (NULL);
	token_struct->token_type = get_token_type(token);
	return (token_struct);
}

static void	*max_token_size_reached(t_list **token_lst, char *buffer)
{
	ft_lstclear(token_lst, clear_token_struct);
	write(2, "Command too long : ", 19);
	write(2, rl_line_buffer, ft_strlen(rl_line_buffer));
	write(2, "\n", 1);
	free(buffer);
	return (NULL);
}

static char	*init(int *i, t_list **token_lst, char **cmd_buffer)
{
	char	*buffer;

	*token_lst = NULL;
	*i = 0;
	skip_spaces(cmd_buffer);
	buffer = xxmalloc(sizeof(char) * MAX_TOKEN_SIZE);
	ft_bzero(buffer, MAX_TOKEN_SIZE);
	return (buffer);
}

t_list	*get_token(char *cmd_buffer)
{
	t_list	*token_lst;
	int		i;
	char	*buffer;

	buffer = init(&i, &token_lst, &cmd_buffer);
	while (*cmd_buffer)
	{
		if (*cmd_buffer == '\"' || *cmd_buffer == '\'')
			i = lex_quotes(&token_lst, &cmd_buffer, &buffer);
		else if (*cmd_buffer == '<' || *cmd_buffer == '>' || *cmd_buffer == '|')
			i = lex_operators(&token_lst, &cmd_buffer, &buffer);
		else if (*cmd_buffer == ' ')
			i = lex_spaces(&token_lst, &cmd_buffer, &buffer);
		else if (*cmd_buffer == '$' && *(cmd_buffer + 1) && *(cmd_buffer + 1)
			!= '$' && *(cmd_buffer + 1) != ' ')
			i = lex_expansion(&token_lst, &cmd_buffer, &buffer);
		else
			i = lex_chars(i, &cmd_buffer, &buffer);
		if (i >= MAX_TOKEN_SIZE - 1)
			return (max_token_size_reached(&token_lst, buffer));
	}
	if (ft_strlen(buffer))
		ft_lstadd_back(&token_lst, ft_lstnew(write_token(buffer)));
	free(buffer);
	return (token_lst);
}
