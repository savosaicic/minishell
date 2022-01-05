/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboisser <jboisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:39:11 by jboisser          #+#    #+#             */
/*   Updated: 2020/12/01 10:18:55 by jboisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_line(char *str)
{
	unsigned int	i;
	char			*one_line;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	one_line = malloc(sizeof(*one_line) * i + 1);
	if (!one_line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		one_line[i] = str[i];
		i++;
	}
	one_line[i] = '\0';
	return (one_line);
}

char	*get_buf_saved(char *str)
{
	unsigned int	i;
	unsigned int	j;
	char			*save;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	save = malloc(sizeof(*save) * (ft_strlen(str) - i) + 1);
	if (!save)
		return (NULL);
	j = 0;
	i++;
	while (str[i])
		save[j++] = str[i++];
	save[j] = '\0';
	free(str);
	return (save);
}

int	gnl_return(int position)
{
	if (position == 0)
		return (0);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*str;
	int			position;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	buf = malloc(sizeof(*buf) * BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	position = 1;
	while (!is_line(str) && position != 0)
	{
		position = read(fd, buf, BUFFER_SIZE);
		if (position == -1)
		{
			free(buf);
			return (-1);
		}
		buf[position] = '\0';
		str = ft_memjoin(str, buf);
	}
	free(buf);
	*line = get_line(str);
	str = get_buf_saved(str);
	return (gnl_return(position));
}
