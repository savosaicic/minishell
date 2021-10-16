#include "minishell.h"

void	echo(t_cmd *cmd)
{
	int option;
	int i;

	if (!cmd->args[1])
	{
		ft_putchar('\n');
		return;
	}
	option = 0;
	i = 1;
	if (!ft_strcmp(cmd->args[1], "-n"))
	{
		option = 1;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr(cmd->args[i]);
		if (cmd->args[i + 1])
			ft_putstr(" ");
		i++;
	}
	if (!option)
		ft_putchar('\n');
}