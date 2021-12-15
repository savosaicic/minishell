/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/15 14:52:32 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*perform_expansion(t_prg *g_prg, t_list *env_lst, char **cmd_buffer)
{
	char	buffer[4096];
	char	*expanded_var;
	char	*tmp;
	int		i;

	ft_bzero(buffer, 4096);
	(*cmd_buffer)++;
	i = 0;
	while (**cmd_buffer)
	{
		if (is_space(**cmd_buffer) || **cmd_buffer == '$'
			|| **cmd_buffer == '\"' || **cmd_buffer == '\'')
			break ;
		buffer[i++] = **cmd_buffer;
		(*cmd_buffer)++;
	}
	if (buffer[0] == '?')
		return (ft_itoa(g_prg->exit_status));
	tmp = ft_getenv(env_lst, buffer);
	if (!tmp)
		expanded_var = ft_strdup("");
	else
		expanded_var = ft_strdup(ft_getenv(env_lst, buffer));
	free(tmp);
	return (expanded_var);
}

static void	split_buffer_and_add_back(char **buffer, t_list **token_lst)
{
	char	**res;
	int		i;

	res = ft_split(*buffer, ' ');
	if (!res)
		return ;
	i = 0;
	while (res[i])
	{
		ft_lstadd_back(token_lst, ft_lstnew(write_token(res[i])));
		i++;
	}
	free_tab(res);
	free(*buffer);
	*buffer = NULL;
}

char	*handle_expansion(t_prg *g_prg, char **cmd_buffer, char **save,
	t_list **token_lst)
{
	char	*expanded_var;
	char	*buffer;

	if (*save)
	{
		buffer = ft_strdup(*save);
		free(*save);
		*save = NULL;
	}
	else
		buffer = ft_strdup("");
	while (**cmd_buffer && !is_space(**cmd_buffer)
		&& **cmd_buffer != '\"' && **cmd_buffer != '\'')
	{
		expanded_var = perform_expansion(g_prg, g_prg->env_lst, cmd_buffer);
		buffer = ft_memjoin(buffer, expanded_var);
		free(expanded_var);
	}
	if (**cmd_buffer != '\"' && **cmd_buffer != '\'')
		split_buffer_and_add_back(&buffer, token_lst);
	return (buffer);
}
