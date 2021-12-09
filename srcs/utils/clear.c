#include "minishell.h"

void	clear_token_struct(void *token_struct)
{
	if (!token_struct)
		return ;
	free(((t_token *)token_struct)->token);
	((t_token *)token_struct)->token = NULL;
	free((t_token *)token_struct);
	token_struct = NULL;
}

void	clear_cmd_struct(void *cmd_struct)
{
	int	i;

	if (!cmd_struct)
		return ;
	i = 0;
	while (((t_cmd *)cmd_struct)->args[i] != NULL)
	{
		free(((t_cmd *)cmd_struct)->args[i]);
		((t_cmd *)cmd_struct)->args[i] = NULL;
		i++;
	}
	free(((t_cmd *)cmd_struct)->args);
	((t_cmd *)cmd_struct)->args = NULL;
	free(((t_cmd *)cmd_struct)->path);
	((t_cmd *)cmd_struct)->path = NULL;
	free((t_cmd *)cmd_struct);
	cmd_struct = NULL;
}

void	clear_var_struct(void *var_struct)
{
	if (!var_struct)
		return ;
	free(((t_variable *)var_struct)->name);
	((t_variable *)var_struct)->name = NULL;
	free(((t_variable *)var_struct)->value);
	((t_variable *)var_struct)->value = NULL;
	free((t_variable *)var_struct);
	var_struct = NULL;
}

void	clear_prg_struct(void)
{
	if (!prg)
		return ;
	free(rl_line_buffer);
	rl_line_buffer = NULL;
	ft_lstclear(&prg->env_lst, clear_var_struct);
	ft_lstclear(&prg->cmd_lst, clear_cmd_struct);
	free(prg->env_lst);
	prg->env_lst = NULL;
	free(prg->pwd);
	prg->pwd = NULL;
	free(prg->home_path);
	prg->home_path = NULL;
	free(prg);
	prg = NULL;
}