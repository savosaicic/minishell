/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboisser <jboisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 16:02:40 by jboisser          #+#    #+#             */
/*   Updated: 2020/11/24 19:22:25 by jboisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_nbrlen(long n_abs, int sign)
{
	unsigned int	n_len;

	if (n_abs == 0)
		return (1);
	n_len = 0;
	while (n_abs > 0)
	{
		n_abs /= 10;
		n_len++;
	}
	if (sign == -1)
		n_len++;
	return (n_len);
}

static void	convert_nb(char *n_str, long n_abs, unsigned int n_len,
		int sign)
{
	n_str[n_len] = '\0';
	n_str[--n_len] = n_abs % 10 + '0';
	n_abs /= 10;
	while (n_abs > 0)
	{
		n_str[--n_len] = n_abs % 10 + '0';
		n_abs /= 10;
	}
	if (sign == -1)
		n_str[0] = '-';
}

char	*ft_itoa(int n)
{
	char			*n_str;
	long			n_abs;
	unsigned int	n_len;
	int				sign;

	sign = 1;
	if (n < 0)
	{
		n_abs = (long)n * -1;
		sign = -1;
	}
	else
		n_abs = n;
	n_len = ft_nbrlen(n_abs, sign);
	n_str = malloc(sizeof(char) * (n_len + 1));
	if (!n_str)
		return (NULL);
	convert_nb(n_str, n_abs, n_len, sign);
	return (n_str);
}
