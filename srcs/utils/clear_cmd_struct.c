#include "minishell.h"

/*
**	this function must me call by ft_lstclear()
**	void *cmd_struct NEED to point on a t_cmd structure
*/
void	clear_cmd_struct(void *cmd_struct)
{
	int	i;

	if (!cmd_struct)
		return ;

	i = 0;
	while (((t_cmd *)cmd_struct)->args[i] != NULL)
	{
		free( ((t_cmd *)cmd_struct)->args[i]);
		i++;
	}
	free(((t_cmd *)cmd_struct)->args);
	free(((t_cmd *)cmd_struct)->path);
	free((t_cmd *)cmd_struct);
}