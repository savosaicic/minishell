#include "minishell.h"

void    sig_int(int sig __attribute__((unused)))
{
    rl_replace_line("", 1);
    dprintf(2, "\n$> ");
}

void sig_quit(int sig __attribute__((unused)))
{
    ft_putstr_fd("\b\b  \b\b", 2);
}

void    manage_signals(void)
{
    signal(SIGINT, &sig_int);
    signal(SIGQUIT, &sig_quit);
}