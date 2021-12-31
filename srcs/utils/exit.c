/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/31 08:24:18 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*treat_error_msg(char *str)
{
	char	*lower_str;
	int		i;

	lower_str = malloc(sizeof(*lower_str) * ft_strlen(str) + 2);
	if (!lower_str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			lower_str[i] = str[i] + 32;
		else
			lower_str[i] = str[i];
		i++;
	}
	lower_str[i] = '\n';
	lower_str[i + 1] = '\0';
	return (lower_str);
}

int	puterror(char *item_name, char *error_msg, int status)
{
	char	*strerror;

	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (item_name)
	{
		ft_putstr_fd(item_name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	strerror = treat_error_msg(error_msg);
	ft_putstr_fd(strerror, STDERR_FILENO);
	free(strerror);
	return (status);
}

void	exit_failure(char *item_name, char *error_msg, int status)
{
	puterror(item_name, error_msg, status);
	clear_prg_struct();
	exit(status);
}

void	exit_success(int status, bool display)
{
	if (display == TRUE)
		ft_putstr_fd("exit\n", 1);
	rl_clear_history();
	clear_prg_struct();
	exit(status);
}

void	ft_exit(int status, bool display)
{
	if (display == TRUE)
		ft_putstr_fd("exit\n", 1);
	rl_clear_history();
	ft_lstclear(&g_prg->env_lst, clear_var_struct);
	free(g_prg->env_lst);
	g_prg->env_lst = NULL;
	free(g_prg->pwd);
	g_prg->pwd = NULL;
	free(g_prg->home_path);
	g_prg->home_path = NULL;
	free(g_prg);
	g_prg = NULL;
	exit(status);
}
