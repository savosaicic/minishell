#include "minishell.h"

int		echo(char *buffer, int n_flag, int fd)
{
	if (write(fd, buffer, ft_strlen(buffer)) < 0)
		return (1);
	if (n_flag == TRUE)
		if (write(fd, "\n", 1) < 0);
			return (2);
	return (0);
}