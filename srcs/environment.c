#include "minishell.h"

t_list *init_env(char **env)
{
	t_list		*env_lst;
	int			i;

	env_lst = NULL;
	i = 0;
	while (env[i])
	{
		ft_lstadd_back(&env_lst, ft_lstnew(write_variable(env[i])));
		i++;
	}
	return (env_lst);
}

void add_var_in_env(t_prg *prg, char *variable)
{
    
}