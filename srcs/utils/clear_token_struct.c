
#include "minishell.h"

/*
**	this function must me call by ft_lstclear()
**	void *token_struct NEED to point on a t_token structure
*/
void	clear_token_struct(void *token_struct)
{
	if (!token_struct)
		return ;
	free(((t_token *)token_struct)->token);
	((t_token *)token_struct)->token = NULL;

	free((t_token *)token_struct);
	token_struct = NULL;
}