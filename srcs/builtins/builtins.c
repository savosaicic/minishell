#include "minishell.h"

static char *clean_message(char *original_string, int option)
{
    int i;
    int k;
    char *rm;
    char *message;

    if (option)
        rm = ft_strdup("echo-n");
    else
        rm = ft_strdup("echo");
    if (!rm)
        return (NULL);
    i = 0;
    k = 0;
    while (original_string[i])
    {
        if (original_string[i] == rm[k])
        {
            i++;
            k++;
        }
        else if (k < ft_strlen(rm))
            i++;
        else break;
    }
    while (original_string[i] == ' ' || original_string[i] == '\t')
        i++;
    message = malloc(sizeof(*message) * (ft_strlen(original_string) - i) + 1);
    if (!message)
        return (NULL);
    k = 0;
    while (original_string[i])
    {
        message[k] = original_string[k + i];
        k++;
    }
    message[k] = '\0';
    return (message);

}

void	echo(t_prg *prg, t_cmd *cmd)
{
    (void)prg;
    char *message;
    int option;
    int i;

    (void)option;
    option = 0;
    i = 0;
    if (ft_strcmp(cmd->args[1], "-n") == 0)
    {
        option = 1;
        i++;
    }
    message = clean_message(cmd->string, option);
    ft_putstr(message);
    if (!option)
        ft_putchar('\n');
    free(message);
}

int     execute_builtin(t_prg *prg, t_cmd *cmd)
{
    echo(prg, cmd);
    return (0);
}