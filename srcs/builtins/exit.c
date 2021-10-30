#include "minishell.h"

int exit_shell(t_prg *prg, t_cmd *cmd)
{
    if (ft_charlen(cmd->args) > 2)
		return (write_error_msg("minishell", "exit", "too many arguments", 1));
    else if (cmd->args[1])
        exit_success(prg, ft_atoi(cmd->args[1]));
    else 
        exit_success(prg, 0);
    return (1);
}