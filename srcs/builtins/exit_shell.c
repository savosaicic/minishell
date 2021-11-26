#include "minishell.h"

int exit_shell(t_cmd *cmd)
{
    if (ft_charlen(cmd->args) > 2)
		return (write_error_msg("minishell", "exit", "too many arguments", 1));
    else if (cmd->args[1] && cmd->args[1][0] == '-' && ft_strcmp(cmd->args[1], "-9223372036854775808") > 0)
        exit(write_error_msg("minishell", "exit", "numeric argument required", 255));
    else if (cmd->args[1] && ft_strcmp(cmd->args[1], "9223372036854775807") > 0)
        exit(write_error_msg("minishell", "exit", "numeric argument required", 255));
    else
    {
        ft_putstr("exit\n");
        exit_success(ft_atoi(cmd->args[1]));
    }
    return (1);
}