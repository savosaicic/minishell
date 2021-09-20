#include "minishell.h"

void	echo(t_prg *prg, char **cmd_args)
{
    (void)prg;
    (void)cmd_args;
    int line_return;
    int i;

    (void)line_return;
    line_return = 0;
    i = 0;
    if (ft_strcmp(cmd_args[1], "-n") == 0)
    {
        line_return = 1;
        i++;
    }
    printf("option %d\n", line_return);
    while (cmd_args[i])
    {
        printf(">%s\n", cmd_args[i++]);

    }
    exit(0);
}

int     execute_builtin(t_prg *prg, t_cmd *cmd)
{
    echo(prg, cmd->args + 1);
    return (0);
}