/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/14 10:00:44 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env(t_list *env_lst, char *str)
{
	if (!env_lst->content && !env_lst->next)
		return (0);
	while (env_lst)
	{
		ft_putstr(str);
		ft_putstr(((t_variable *)env_lst->content)->name);
		ft_putchar('=');
		ft_putstr(((t_variable *)env_lst->content)->value);
		ft_putchar('\n');
		env_lst = env_lst->next;
	}
	return (0);
}

int	export(t_cmd *cmd, t_list *env_lst)
{
	int	i;

	if (ft_charlen(cmd->args) <= 1)
		return (print_env(env_lst, "export "));
	if (cmd->args[1][0] == '-')
		return (puterror("-", "not a valid identifier", 1));
	else if (!cmd->args[1][0])
		return (puterror("export", "`': not a valid identifier", 1));
	i = 1;
	while (cmd->args[i])
	{
		ft_envlst_add_back(&env_lst, ft_lstnew(write_variable(cmd->args[i])));
		i++;
	}
	return (0);
}

void	delete_variable(t_list *env_lst, char *del)
{
	t_list	*next;

	if (!ft_strcmp(((t_variable *)env_lst->content)->name, del))
	{
		next = env_lst->next;
		free_lstvar(env_lst);
		if (next)
		{
			*env_lst = *next;
			free(next);
		}
		else
		{
			env_lst->content = NULL;
			env_lst->next = NULL;
			return ;
		}
	}
	next = env_lst->next;
	while (next)
	{
		if (!ft_strcmp(((t_variable *)next->content)->name, del))
		{
			env_lst->next = next->next;
			free_lstvar(next);
			free(next);
			return ;
		}
		env_lst = env_lst->next;
		next = next->next;
	}
}

int	unset(t_cmd *cmd, t_list *env_lst)
{
	int	i;
	int	ret;

	ret = 0;
	if (ft_charlen(cmd->args) <= 1)
		return (puterror("unset", "not enough arguments", 1));
	if (cmd->args[1][0] == '-')
		return (puterror("-", "not a valid identifier", 1));
	i = 1;
	while (cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], '/') || ft_strchr(cmd->args[i], '.'))
			ret = puterror(cmd->args[i], "not a valid identifier", 1);
		if (ft_lstsearch(env_lst, cmd->args[i]))
			delete_variable(env_lst, cmd->args[i]);
		i++;
	}
	return (ret);
}
