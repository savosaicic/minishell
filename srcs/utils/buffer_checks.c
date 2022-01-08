/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/14 09:08:30 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_forbidden_char_error(char fchar)
{
	char	error_buffer[32];

	ft_bzero(&error_buffer[0], 32);
	ft_strlcpy(error_buffer, "minishell: forbidden char: ", 28);
	error_buffer[27] = '`';
	error_buffer[28] = fchar;
	ft_strcat(error_buffer, "\'\n");
	return (write(2, error_buffer, 32));
}

static int	write_unclosed_quote_error(char quote)
{
	char	error_buffer[32];

	ft_bzero(&error_buffer[0], 32);
	ft_strlcpy(error_buffer, "minishell: unclosed quote: ", 28);
	error_buffer[27] = '`';
	error_buffer[28] = quote;
	ft_strcat(error_buffer, "\'\n");
	return (write(2, error_buffer, 32));
}

// static int	check_assign_error(char *buffer)
// {
// 	char **buffer_split;
// 	int i;
// 	int j;
// 	bool assign;

// 	buffer_split = ft_split(buffer, '|');
// 	if (!buffer_split)
// 		return (0);
// 	i = 0;
// 	while (buffer_split[i])
// 	{
// 		j = 0;
// 		assign = true;
// 		while (buffer_split[i][j])
// 		{

// 		}
// 	}
// 	while (*buffer)

// }

int	check_quote_and_forbiden_char(char *buffer)
{
	int	simple_quote;
	int	double_quote;
	int 	i;

	simple_quote = 0;
	double_quote = 0;
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\'')
			simple_quote++;
		else if (buffer[i] == '\"')
			double_quote++;
		else if (buffer[i] == ';' || buffer[i] == '\\')
			return (write_forbidden_char_error(buffer[i]));
		i++;
	}
	if (simple_quote % 2 != 0)
		return (write_unclosed_quote_error('\''));
	if (double_quote % 2 != 0)
		return (write_unclosed_quote_error('\"'));
	// return (check_assign_error(buffer));
	return(0);
}
