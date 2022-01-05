/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboisser <jboisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:15:55 by jboisser          #+#    #+#             */
/*   Updated: 2020/11/25 15:16:59 by jboisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ischarset(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strtrim;
	size_t	i;
	size_t	start;
	size_t	end;

	if (s1 == NULL)
		return (NULL);
	start = 0;
	while (s1[start] && (ft_ischarset(set, s1[start]) == 1))
		start++;
	end = ft_strlen(s1);
	while (end > start && (ft_ischarset(set, s1[end - 1]) == 1))
		end--;
	strtrim = malloc(sizeof(char) * (end - start + 1));
	if (!strtrim)
		return (NULL);
	i = 0;
	while (start < end)
	{
		strtrim[i] = s1[start];
		start++;
		i++;
	}
	strtrim[i] = '\0';
	return (strtrim);
}
