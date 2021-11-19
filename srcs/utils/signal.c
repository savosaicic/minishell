#include "minishell.h"

void    sig_int(int sig __attribute__((unused)))
{
    rl_replace_line("", 0);
    rl_on_new_line();
    ft_putstr_fd("\n", 1);
    rl_redisplay();
}

void    sig_quit(int sig __attribute__((unused)))
{
    ft_putstr_fd("\b\b  \b\b", 1);
}

void    manage_signals(void)
{
    signal(SIGINT, &sig_int);
    signal(SIGQUIT, &sig_quit);
}