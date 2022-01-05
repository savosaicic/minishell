/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboisser <jboisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 22:49:26 by jboisser          #+#    #+#             */
/*   Updated: 2020/11/23 15:59:30 by jboisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*enew;

	if (!content)
		return (NULL);
	enew = (t_list *)malloc(sizeof(*enew));
	if (enew == NULL)
		return (NULL);
	enew->content = content;
	enew->next = NULL;
	return (enew);
}
