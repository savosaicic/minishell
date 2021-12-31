/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_savo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 09:02:44 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/31 14:49:21 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_wdcount(char const *s, char c)
{
	size_t	i;
	int		wd;

	wd = 0;
	if (s[0] != c && s[0] != '\0')
		wd++;
	i = 0;
	while (i < ft_strlen(s))
	{
		while (s[i] == c && s[i])
		{
			if (s[i + 1] != c && s[i + 1] != '\0')
				wd++;
			i++;
		}
		i++;
	}
	return (wd);
}

static	int	*ft_charcount(char const *s, char c)
{
	int	i;
	int	j;
	int	*ccount;

	i = 0;
	while (s[i] == c)
		i++;
	ccount = (int *)malloc(sizeof(int) * ft_wdcount(s, c));
	if (!ccount)
		return (NULL);
	j = 0;
	while (j < ft_wdcount(s, c))
	{
		ccount[j] = 0;
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i])
		{
			ccount[j]++;
			i++;
		}
		j++;
	}
	return (ccount);
}

static	char	**ft_filltab(char **tab, char const *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (s[i] == c)
		i++;
	j = 0;
	while (j < ft_wdcount(s, c))
	{
		k = 0;
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i])
		{
			tab[j][k] = s[i];
			i++;
			k++;
			if (s[i] == c || s[i] == '\0')
				tab[j][k] = '\0';
		}
		j++;
	}
	return (tab);
}

static	void	*ft_free_tab(char **tab, int wd)
{
	int	i;

	i = 0;
	while (i < wd)
	{
		free(tab[i]);
		i++;
	}
	free(tab[i]);
	return (NULL);
}

char	**ft_split_savo(char const *s, char c)
{
	int		i;
	int		*charnb;
	char	**tab;

	if (!s)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_wdcount(s, c) + 1));
	if (!tab)
		return (NULL);
	charnb = ft_charcount(s, c);
	i = 0;
	while (i < ft_wdcount(s, c))
	{
		tab[i] = (char *)malloc(sizeof(char) * (charnb[i] + 1));
		if (!tab[i])
			return (ft_free_tab(tab, i));
		i++;
	}
	ft_filltab(tab, s, c);
	tab[i] = NULL;
	free(charnb);
	return (tab);
}
