/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboisser <jboisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:14:57 by jboisser          #+#    #+#             */
/*   Updated: 2020/11/24 18:35:49 by jboisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s1_copy;

	i = 0;
	while (s1[i])
	{
		i++;
	}
	i++;
	s1_copy = (char *)malloc(sizeof(*s1_copy) * i);
	if (s1_copy == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s1_copy[i] = s1[i];
		i++;
	}
	s1_copy[i] = '\0';
	return (s1_copy);
}
