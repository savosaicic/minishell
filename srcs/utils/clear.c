/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboisser <jboisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by jboisser          #+#    #+#             */
/*   Updated: 2021/12/14 10:24:06 by jboisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (!g_prg)
		return ;
	free(g_prg->cmd_buffer);
	g_prg->cmd_buffer = NULL;
	ft_lstclear(&g_prg->env_lst, clear_var_struct);
	ft_lstclear(&g_prg->cmd_lst, clear_cmd_struct);
	free(g_prg->env_lst);
	g_prg->env_lst = NULL;
	free(g_prg->pwd);
	g_prg->pwd = NULL;
	free(g_prg->home_path);
	g_prg->home_path = NULL;
	free(g_prg);
	g_prg = NULL;
}
