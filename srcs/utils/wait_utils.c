/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboisser <jboisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/01 15:37:34 by jboisser          #+#    #+#             */
/*   Updated: 2022/01/01 15:37:37 by jboisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	idx_pid_max(t_exit *exit_struct, int len)
{
	int	i;
	int	i_max;

	i = 0;
	i_max = 0;
	while (i < len)
	{
		if (exit_struct[i].pid_ret > exit_struct[i_max].pid_ret)
			i_max = i;
		i++;
	}
	return (i_max);
}

t_exit	*set_exit_struct(void)
{
	t_exit	*exit_struct;
	int		i;

	i = 0;
	exit_struct = xxmalloc(sizeof(t_exit) * g_prg->cmds_len);
	while (i < g_prg->cmds_len)
	{
		exit_struct[i].pid_ret = 1;
		exit_struct[i].value = 0;
		i++;
	}
	return (exit_struct);
}

int	wait_pid(pid_t pid)
{
	int	ret;
	int	status;

	status = 0;
	ret = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		ret = WTERMSIG(status) + 128;
	return (ret);
}

void	wait_all_pids(void)
{
	t_exit	*exit_struct;
	int		status;
	int		i;

	i = 0;
	status = 0;
	exit_struct = set_exit_struct();
	while (i < g_prg->cmds_len && exit_struct[i].pid_ret > 0)
	{
		exit_struct[i].pid_ret = wait(&status);
		if (WIFEXITED(status))
			exit_struct[i].value = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_struct[i].value = WTERMSIG(status);
		i++;
	}
	g_prg->exit_status
		= exit_struct[idx_pid_max(exit_struct, g_prg->cmds_len)].value;
	free(exit_struct);
	exit_struct = NULL;
}
