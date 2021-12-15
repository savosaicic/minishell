/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/15 15:05:50 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*quotes_expansion(t_prg *g_prg, t_list *env_lst, char **cmd_buffer,
	char quote)
{
	char	buffer[4096];
	char	*expanded_var;
	int		i;

	ft_bzero(buffer, 4096);
	(*cmd_buffer)++;
	i = 0;
	while (**cmd_buffer && **cmd_buffer != quote)
	{
		if (is_space(**cmd_buffer) || **cmd_buffer == '$')
			break ;
		buffer[i++] = **cmd_buffer;
		(*cmd_buffer)++;
	}
	if (buffer[0] == '?')
		return (ft_itoa(g_prg->exit_status));
	expanded_var = ft_getenv(env_lst, buffer);
	if (!expanded_var)
		return (ft_strdup(""));
	return (expanded_var);
}

static void	init_vars(char **cmd_buffer, int *i, char *quote, char *buffer)
{
	*quote = **cmd_buffer;
	(*cmd_buffer)++;
	*i = 0;
	ft_bzero(buffer, 4096);
}

int	need_to_expand(char **cmd_buffer, char quote)
{
	return (**cmd_buffer == '$' && *(*cmd_buffer + 1) && *(*cmd_buffer + 1)
		!= '$' && *(*cmd_buffer + 1) != ' ' && quote != '\'');
}

char	*handle_quote(t_prg *g_prg, char **cmd_buffer, char *str)
{
	char	quote;
	char	buffer[4096];
	int		i;
	char	*tmp;

	init_vars(cmd_buffer, &i, &quote, &buffer[0]);
	while (**cmd_buffer != quote && **cmd_buffer)
	{
		while (need_to_expand(cmd_buffer, quote))
		{
			tmp = quotes_expansion(g_prg, g_prg->env_lst, cmd_buffer, quote);
			ft_strcat(buffer, tmp);
			i += ft_strlen(tmp);
			free(tmp);
			if (**cmd_buffer == quote)
				break ;
		}
		if (**cmd_buffer == quote)
			break ;
		buffer[i++] = *(*cmd_buffer)++;
	}
	(*cmd_buffer)++;
	if (str)
		return (ft_strjoin(str, &buffer[0]));
	if (ft_strlen(buffer))
		return (ft_strdup(&buffer[0]));
	return (NULL);
}
