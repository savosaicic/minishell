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
		free(((t_cmd *)cmd_struct)->args[i]);
		i++;
	}
	free(((t_cmd *)cmd_struct)->args);
	free(((t_cmd *)cmd_struct)->path);
	free((t_cmd *)cmd_struct);
}

void	clear_var_struct(void *var_struct)
{
	if (!var_struct)
		return ;
	free(((t_variable *)var_struct)->name);
	free(((t_variable *)var_struct)->value);
}

void	clear_prg_struct(void)
{
	if (!prg)
		return ;
	free(rl_line_buffer);
	free(prg->env_lst);
	free(prg->pwd);
	free(prg);
}