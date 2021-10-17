#include "minishell.h"

int export(t_cmd *cmd, t_list *env_lst)
{
    int i;

	if (cmd->args[1][0] == '-')
		return (write_error_msg("minishell", "-", "not a valid identifier", 1));
	i = 1;
	while (cmd->args[i])
	{
    	ft_lstadd_back(&env_lst, ft_lstnew(write_variable(cmd->args[i])));
		i++;
	}
	return (0);
}