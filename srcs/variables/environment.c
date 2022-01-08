/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2022/01/01 15:17:18 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_list *env_lst, char *var_search)
{
	while (env_lst)
	{
		if (!ft_strcmp(((t_variable *)(env_lst->content))->name, var_search))
			return (ft_strdup(((t_variable *)(env_lst->content))->value));
		env_lst = env_lst->next;
	}
	return (NULL);
}

t_variable	*write_variable(char *var, bool replace)
{
	t_variable	*var_struct;
	int			i;

	if (!ft_strchr(var, '='))
		return (NULL);
	var_struct = xxmalloc(sizeof(*var_struct));
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	var_struct->name = xxmalloc(sizeof(char) * (i + 1));
	i = 0;
	while (var[i] && var[i] != '=')
	{
		var_struct->name[i] = var[i];
		i++;
	}
	var_struct->name[i] = '\0';
	if (replace && ft_lstsearch(g_prg->env_lst, var_struct->name))
	{
		delete_variable(g_prg->env_lst, var_struct->name);
	}
	var_struct->value = ft_strdup(var + i + 1);
	return (var_struct);
}

t_list	*init_env(void)
{
	t_list	*env_lst;
	int		i;

	if (!g_prg->env)
		return (NULL);
	env_lst = NULL;
	i = 0;
	while (g_prg->env[i])
		ft_lstadd_back(&env_lst, ft_lstnew(write_variable(g_prg->env[i++],
					false)));
	return (env_lst);
}
