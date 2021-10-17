#include "minishell.h"

int	write_error_msg(char *bin_name, char *item_name, char *error_msg, int status)
{
	write(2, bin_name, ft_strlen(bin_name));
	write(2, ": ", 2);
	write(2, item_name, ft_strlen(item_name));
	write(2, ": ", 2);
	write(2, error_msg, ft_strlen(error_msg));
	write(2, "\n", 1);
	return (status);
}

void	exit_failure(t_prg *prg, t_cmd *cmd, char *error_msg, int status)
{
	(void)cmd;
	(void)error_msg;
	clear_prg_struct(prg);
	// write_error_msg("minishell", cmd->args[0], error_msg);
	exit(status);
}

void	exit_success(t_prg *prg, int status)
{
	rl_clear_history();
	clear_prg_struct(prg);
	exit(status);

}