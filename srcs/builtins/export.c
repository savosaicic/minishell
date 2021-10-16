#include "minishell.h"

void export(t_cmd *cmd, t_list *env_lst)
{
    (void)cmd;
    int i;

	i = 1;
	while (cmd->args[i])
	{
    	ft_lstadd_back(&env_lst, ft_lstnew(write_variable(cmd->args[i])));
		i++;
	}
}