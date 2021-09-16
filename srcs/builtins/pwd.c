#include "minishell.h"

int		pwd(void)
{
	char	buffer[BUFFER_SIZE];

	if (get_cwd(buffer, BUFFER_SIZE))
		return (1);
	write(1, buffer, ft_strlen(buffer));
	return (0);
}
