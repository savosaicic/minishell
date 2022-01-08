/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jboisser <jboisser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by jboisser          #+#    #+#             */
/*   Updated: 2021/12/30 14:46:09 by jboisser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int sig __attribute__((unused)))
{
	if (g_prg->in_heredoc)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		close(STDIN_FILENO);
		g_prg->sig_int = 1;
	}
	else if (!g_prg->child)
	{
		rl_replace_line("", 0);
		ft_putchar_fd('\n', 2);
		ft_putstr_fd(rl_prompt, 2);
		rl_on_new_line_with_prompt();
	}
	else if (g_prg->pid)
		ft_putstr_fd("\n", 2);
}

void	sig_quit(int sig __attribute__((unused)))
{
	if (g_prg->pid)
		ft_putstr_fd("\n", 2);
}

void	watch_signals(void)
{
	if (signal(SIGINT, &sig_int) == SIG_ERR)
		exit_failure(NULL, strerror(errno), 1);
	if (signal(SIGQUIT, &sig_quit) == SIG_ERR)
		exit_failure(NULL, strerror(errno), 1);
}
