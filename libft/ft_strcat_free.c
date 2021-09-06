/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboisser <jboisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:08:37 by jboisser          #+#    #+#             */
/*   Updated: 2020/11/20 18:11:23 by jboisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcat_free(char **str, char *buf)
{
	char	*tmp;

	if (*str == NULL)
		*str = ft_strdup(buf);
	else if (**str == '\0')
	{
		free(*str);
		*str = ft_strdup(buf);
	}
	else
	{
		tmp = ft_strdup(*str);
		free(*str);
		*str = ft_strjoin(tmp, buf);
		free(tmp);
	}
}
