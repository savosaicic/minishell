#include "minishell.h"

void	exit_failure(t_prg *prg, char *str, int status)
{
	// clean(prg)
	exit(status);
}