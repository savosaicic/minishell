/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_savo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:02:44 by sasaicic          #+#    #+#             */
/*   Updated: 2022/01/01 12:08:59 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char *s, char c)
{
	int	wdcount;

	if (!s)
		return (0);
	wdcount = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			return (wdcount);
		else
		{
			while (*s && *s != c)
				s++;
			wdcount++;
		}
	}
	return (wdcount);
}

static char	*ft_strdup_sep(char **s, char c)
{
	char	*str;
	int		i;

	i = 0;
	while (*(*s + i) && *(*s + i) != c)
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (**s && **s != c)
		str[i++] = *(*s)++;
	str[i] = '\0';
	return (str);
}

char	**ft_split_savo(char const *s, char c)
{
	char	**tab;
	int		wdcount;
	int		i;
	char	*cpy;

	if (!s)
		return (NULL);
	wdcount = word_count((char *)s, c);
	tab = malloc(sizeof(char *) * (wdcount + 1));
	if (!tab)
		return (NULL);
	i = 0;
	cpy = (char *)s;
	while (i < wdcount)
	{
		while (*cpy == c)
			cpy++;
		tab[i++] = ft_strdup_sep(&cpy, c);
	}
	tab[i] = NULL;
	return (tab);
}
