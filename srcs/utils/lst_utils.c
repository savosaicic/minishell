/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/14 09:08:30 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_envlst_add_back(t_list **alst, t_list *new)
{
	t_list	*last;

	if (alst)
	{
		if (*alst)
		{
			last = ft_lstsearch(*alst, ((t_variable *)new->content)->name);
			if (!last)
			{
				last = ft_lstlast(*alst);
				last->next = new;
			}
			else
				((t_variable *)last->content)->value
					= ((t_variable *)new->content)->value;
		}
		else
			*alst = new;
	}
}

t_list	*ft_lstsearch(t_list *lst, char *search)
{
	t_list	*prev;

	prev = NULL;
	while (lst)
	{
		prev = lst;
		if (!ft_strcmp(((t_variable *)lst->content)->name, search))
			return (prev);
		lst = lst->next;
	}
	return (NULL);
}
