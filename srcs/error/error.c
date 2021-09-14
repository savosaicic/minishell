#include "minishell.h"

void	exit_failure(t_prg *prg, char *str, int status)
{
	(void)prg;
	(void)str;
	// clean(prg)
	exit(status);
}
