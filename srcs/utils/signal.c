/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/14 10:12:45 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int sig __attribute__((unused)))
{
	if (!g_prg->child)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr_fd("\n", 2);
		rl_redisplay();
	}
	else if (g_prg->pid)
		ft_putstr_fd("\n", 2);
}

void	sig_quit(int sig __attribute__((unused)))
{
	ft_putstr_fd("\b\b  \b\b", 1);
}

void	watch_signals(void)
{
	if (signal(SIGINT, &sig_int) == SIG_ERR)
		exit_failure(NULL, strerror(errno), 1);
	if (signal(SIGQUIT, &sig_quit) == SIG_ERR)
		exit_failure(NULL, strerror(errno), 1);
}
