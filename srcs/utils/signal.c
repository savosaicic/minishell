#include "minishell.h"

void    sig_int(int sig __attribute__((unused)))
{
    rl_replace_line("", 0);
    rl_on_new_line();
    ft_putstr_fd("\n", 2);
    rl_redisplay();
}

void    sig_quit(int sig __attribute__((unused)))
{
    ft_putstr_fd("\b\b  \b\b", 1);
}

void    watch_signals(void)
{
    if (signal(SIGINT, &sig_int) == SIG_ERR)
        exit(write_error_msg("minishell", strerror(errno), NULL, 1));
    if (signal(SIGQUIT, &sig_quit) == SIG_ERR)
        exit(write_error_msg("minishell", strerror(errno), NULL, 1));
}


void    unwatch_signals(void)
{
    if (signal(SIGINT, NULL) == SIG_ERR)
        exit(write_error_msg("minishell", strerror(errno), NULL, 1));
    if (signal(SIGQUIT, NULL) == SIG_ERR)
        exit(write_error_msg("minishell", strerror(errno), NULL, 1));
}