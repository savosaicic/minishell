/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboisser <jboisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:14:39 by jboisser          #+#    #+#             */
/*   Updated: 2020/11/25 17:03:19 by jboisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_malloc_split(char const *s, char c)
{
	size_t	i;
	size_t	count;
	char	**split;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	split = (char **)malloc(sizeof(s) * (count + 2));
	if (!split)
		return (NULL);
	return (split);
}

static void	*ft_free_all(char **split, size_t element)
{
	size_t	i;

	i = 0;
	while (i < element)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static void	*ft_split_part(char **split, char const *s,
		t_split_next *seg, t_split_next *tab)
{
	split[tab->length] = ft_substr(s, seg->start, seg->length);
	if (!split[tab->length])
		return (ft_free_all(split, tab->length));
	tab->length++;
	return (split);
}

static void	*ft_find_split(char **split, char const *s, char c)
{
	size_t			i;
	t_split_next	seg;
	t_split_next	tab;

	i = 0;
	tab.length = 0;
	tab.start = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			seg.start = tab.start;
			seg.length = (i - tab.start);
			if (i > tab.start && !ft_split_part(split, s, &seg, &tab))
				return (NULL);
			tab.start = i + 1;
		}
		i++;
	}
	seg.start = tab.start;
	seg.length = (i - tab.start);
	if (i > tab.start && i > 0 && !ft_split_part(split, s, &seg, &tab))
		return (NULL);
	split[tab.length] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (s == NULL)
		return (NULL);
	split = ft_malloc_split(s, c);
	if (!split)
		return (NULL);
	if (!ft_find_split(split, s, c))
		return (NULL);
	return (split);
}
