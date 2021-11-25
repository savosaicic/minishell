#include "minishell.h"

int	write_error_msg(char *bin_name, char *item_name, char *error_msg, int status)
{
	write(2, bin_name, ft_strlen(bin_name));
	write(2, ": ", 2);
	write(2, item_name, ft_strlen(item_name));
	write(2, ": ", 2);
	if (error_msg && error_msg[0] >= 'A' && error_msg[0] <= 'Z')
	{
		ft_putchar(error_msg[0] + 32);
		write(2, error_msg + 1, ft_strlen(error_msg));
	}
	else
		write(2, error_msg, ft_strlen(error_msg));
	write(2, "\n", 1);
	return (status);
}

void	exit_failure(char *item_name, char *error_msg, int status)
{
	clear_prg_struct();
	write_error_msg("minishell", item_name, error_msg, status);
	exit(status);
}

void	exit_success(int status)
{
	rl_clear_history();
	clear_prg_struct();
	exit(status);
}