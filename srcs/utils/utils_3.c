/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:58:33 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/21 12:07:49 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_onlychr(char *str, char c)
{
	int	i;

	i = 0;
	if (str[i] != c)
		return (0);
	while (str[i])
	{
		if (str[i++] != c)
			return (0);
	}
	return (1);
}
