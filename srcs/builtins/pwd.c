#include "minishell.h"

int		pwd(void)
{
	char	buffer[BUFFER_SIZE];

	if (get_cwd(buffer, BUFFER_SIZE))
		return (1);
	else //If Buffer Size is too small
		(void)buffer; //Change this

	write(1, buffer, ft_strlen(buffer));
	return (0);
}
