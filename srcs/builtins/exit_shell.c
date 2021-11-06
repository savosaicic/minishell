#include "minishell.h"

int exit_shell(t_prg *prg, t_cmd *cmd)
{
    char ret;
    int ret2;

    ret = ft_atoi(cmd->args[1]);
    ret2 = ft_atoi(cmd->args[1]);
    printf("ret %d\n", ret);
    printf("ret2 %d\n", ret2);
    if (ft_charlen(cmd->args) > 2)
		return (write_error_msg("minishell", "exit", "too many arguments", 1));
    // else if (ret == 0 && cmd->args[1][0] == '-')
    // {
    //     return (write_error_msg("minishell", "exit", "numeric argument required", 255));
    //     exit_success(prg, ft_atoi(cmd->args[1]));
    // }
    else if (cmd->args[1])
    {

        exit_success(prg, ret);
    }
    else
        exit_success(prg, 0);
    return (1);
}