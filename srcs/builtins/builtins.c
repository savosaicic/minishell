#include "minishell.h"

static char *str_remove(char *string, char *string_rm)
{
	int i;
	int k;
	char *new_string;

	i = 0;
	k = 0;
	while (string[i])
	{
		if (string[i] == string_rm[k])
		{
			i++;
			k++;
		}
		else if (k < ft_strlen(string_rm))
			i++;
		else break;
	}
	while (string[i] == ' ' || string[i] == '\t')
		i++;
	new_string = ft_strdup(string + i);
	return (new_string);
}

void	echo(t_cmd *cmd)
{
	char *message;
	int option;
	int i;

	option = 0;
	i = 0;
	if (ft_strcmp(cmd->args[1], "-n") == 0)
	{
		option = 1;
		i++;
	}
	if (option)
		message = str_remove(cmd->string, "echo-n");
	else
		message = str_remove(cmd->string, "echo");
	ft_putstr(message);
	if (!option)
		ft_putchar('\n');
	free(message);
}

int     execute_builtin(t_prg *prg, t_cmd *cmd)
{
	echo(cmd);
	return (0);
}
