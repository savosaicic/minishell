/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboisser <jboisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:39:23 by jboisser          #+#    #+#             */
/*   Updated: 2021/03/15 10:29:03 by jboisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memjoin(const char *s1, const char *s2)
{
	char	*str_join;
	size_t	s1_len;
	size_t	s2_len;
	size_t	s_len;

	if (s1 == NULL && s2 == NULL)
		return (0);
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	s_len = s1_len + s2_len;
	str_join = malloc(sizeof(*str_join) * s_len + 1);
	if (!(str_join))
		return (0);
	ft_memmove(str_join, s1, s1_len);
	ft_memmove(str_join + s1_len, s2, s2_len);
	str_join[s_len] = '\0';
	free((char *)s1);
	return (str_join);
}
