#include "minishell.h"

void    sig_int(int signo)
{
    (void)signo;
    // dprintf(1, "\b\b      ");
    // dprintf(2, "\n");

    // dprintf(2, "$> ");
    // ft_putstr_fd("\b\b  ", 2);
	// ft_putstr_fd("\n", 2);
	// ft_putstr_fd("$> ", 2);
    rl_replace_line("salut", 1);
    sigs.sig_int = 1;
}


void    sig_quit(int signo)
{
    (void)signo;
    printf("signal quit\n");
}

void    manage_signals(t_prg *prg)
{
    (void)prg;
    sigs.sig_int = 0;

    signal(SIGINT, &sig_int);
}