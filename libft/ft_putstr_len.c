/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboisser <jboisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 10:50:41 by jboisser          #+#    #+#             */
/*   Updated: 2020/12/19 10:50:43 by jboisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_len(char *s, size_t len)
{
	size_t	size;

	size = 0;
	while (s[size] && size < len)
		ft_putchar(s[size++]);
	return (size);
}
