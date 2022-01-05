/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isdigit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboisser <jboisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 10:50:16 by jboisser          #+#    #+#             */
/*   Updated: 2021/06/29 12:21:09 by boisseran        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_isdigit(char *str)
{
	unsigned int	i;
	int				minus;

	i = 0;
	minus = 0;
	while (str[i])
	{
		if (str[i] == '-' && minus == 0)
			minus = 1;
		else if (!(ft_isdigit(str[i])))
			return (0);
		i++;
	}
	return (1);
}
