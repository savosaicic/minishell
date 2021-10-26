#include "minishell.h"

int print_env(t_list *env_lst)
{
    while (env_lst)
    {
        printf("%s=%s\n", ((t_variable *)env_lst->content)->name, ((t_variable *)env_lst->content)->value);
        env_lst = env_lst->next;
    }
    return (0);
}

int export(t_cmd *cmd, t_list *env_lst)
{
    int i;

	if (cmd->args[1][0] == '-')
		return (write_error_msg("minishell", "-", "not a valid identifier", 1));
	i = 1;
	while (cmd->args[i])
	{
    	ft_envlst_add_back(&env_lst, ft_lstnew(write_variable(cmd->args[i])));
		i++;
	}
	return (0);
}