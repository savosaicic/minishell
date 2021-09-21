/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboisser <jboisser@student.42.fr>          +#+  +:+       +#+        */
/*                                   qqq             +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:15:39 by jboisser          #+#    #+#             */
/*   Updated: 2020/11/20 22:39:55 by jboisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] == (unsigned char)s2[i]
		&& s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
