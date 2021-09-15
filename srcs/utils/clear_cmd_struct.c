
#include "minishell.h"

void	clear_cmd_struct(void *cmd_struct)
{
	int	i;

	i = 0;
	while (((t_cmd *)cmd_struct)->args[i] != NULL)
	{
		free( ((t_cmd *)cmd_struct)->args[i]);
		i++;
	}
	free(((t_cmd *)cmd_struct)->args);
	free((t_cmd *)cmd_struct);
}