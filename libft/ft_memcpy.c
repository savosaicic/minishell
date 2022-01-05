/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboisser <jboisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:13:52 by jboisser          #+#    #+#             */
/*   Updated: 2020/11/24 17:19:54 by jboisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*src_cpy;
	unsigned char	*dst_cpy;

	src_cpy = (unsigned char *)src;
	dst_cpy = (unsigned char *)dst;
	if (!dst_cpy && !src_cpy)
		return (NULL);
	while (n)
	{
		*dst_cpy++ = *src_cpy++;
		n--;
	}
	return (dst);
}
