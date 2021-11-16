#include "minishell.h"

void    sig_int(int signo)
{
    (void)signo;
    // printf("\b\b\n");
    printf("$> ");
}


void    sig_quit(int signo)
{
    (void)signo;
    printf("signal quit\n");
}

void    sig_init(t_prg *prg)
{
    sig.sa_handler = sig_int;
  	if (sigaction(SIGINT, &sig, NULL) < 0)
		exit_failure(prg, NULL, "sh: sigaction failed", 1);
}