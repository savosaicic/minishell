/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboisser <jboisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:13:59 by jboisser          #+#    #+#             */
/*   Updated: 2020/11/24 17:34:38 by jboisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dst_cpy;
	unsigned char	*src_cpy;

	i = 0;
	dst_cpy = (unsigned char *)dst;
	src_cpy = (unsigned char *)src;
	if (!dst_cpy && !src_cpy)
		return (NULL);
	if (dst_cpy > src_cpy)
	{
		while (i < len)
		{
			dst_cpy[len - 1] = src_cpy[len - 1];
			len--;
		}
	}
	else
	{
		while (i++ < len)
		{
			dst_cpy[i - 1] = src_cpy[i - 1];
		}
	}
	return (dst);
}
