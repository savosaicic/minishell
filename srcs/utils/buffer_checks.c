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

int	check_quote_and_forbiden_char(char *buffer)
{
	int	simple_quote;
	int	double_quote;

	simple_quote = 0;
	double_quote = 0;
	while (*buffer)
	{
		if (*buffer == '\'')
			simple_quote++;
		else if (*buffer == '\"')
			double_quote++;
		else if (*buffer == ';' || *buffer == '\\')
			return (write_forbidden_char_error(*buffer));
		buffer++;
	}
	if (simple_quote % 2 != 0)
		return (write_unclosed_quote_error('\''));
	if (double_quote % 2 != 0)
		return (write_unclosed_quote_error('\"'));
	return (0);
}
