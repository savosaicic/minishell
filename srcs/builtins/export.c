#include "minishell.h"

void export(t_cmd *cmd, t_list *env_lst)
{
    (void)cmd;
    int i;

	i = 1;
	while (cmd->args[i])
	{
		// printf("cmd %s\n", cmd->args[i]);
    	ft_lstadd_back(&env_lst, ft_lstnew(write_variable(cmd->args[i])));
		i++;
	}
	// list = NULL;
	// var = write_variable(variable);
	printf("env %s\n", ft_getenv(env_lst, "VAR"));
	// print_variables(env_lst);
}