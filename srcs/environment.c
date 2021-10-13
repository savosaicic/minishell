#include "minishell.h"

static void print_list (t_list *lst)
{
    while (!lst)
    {
        printf("%s\n", ((t_variable *)lst->content)->value);
        lst = lst->next;
    }
}

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

t_variable *write_variable(char *var)
{
	t_variable	*var_struct;
	char		**var_split;

	var_struct = malloc(sizeof(*var_struct));
	if (!var_struct)
		return (NULL);
	var_split = ft_split(var, '=');
	if (!var_split)
	{
		free(var_struct);
		return (NULL);
	}
	var_struct->name = ft_strdup(var_split[0]);
	if (var_split[1])
		var_struct->value = ft_strdup(var_split[1]);
	free_tab(var_split);
	return (var_struct);
}

void add_var_in_env(char *variable, t_list **env_lst)
{
    (void)variable;
    (void)env_lst;
    print_list(*env_lst);
    // ft_lstadd_back(&env_lst, ft_lstnew(write_variable(variable)));

}