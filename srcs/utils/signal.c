#include "minishell.h"

void    sig_int(int sig __attribute__((unused)))
{
    // dprintf(2, "go in sigint\n");
    // dprintf(2, "sig int %d\n", sigs.sig_int);
    sigs.sig_int = 1;
    rl_replace_line("", 0);
    rl_on_new_line();
    ft_putstr_fd("\n", 1);
    rl_redisplay();
}

void    sig_quit(int sig __attribute__((unused)))
{
    // if (!sigs.sig_quit)
    //     return ;
    sigs.sig_quit = 1;
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