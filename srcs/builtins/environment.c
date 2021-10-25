#include "minishell.h"

void print_variables(t_list *lst)
{
    while (lst)
    {
        printf("%s=%s\n", ((t_variable *)lst->content)->name, ((t_variable *)lst->content)->value);
        lst = lst->next;
    }
}

char *ft_getenv(t_list *env_lst, char *var_search)
{
	while (env_lst)
	{
		if (!ft_strcmp(((t_variable *)(env_lst->content))->name, var_search))
			return (ft_strdup(((t_variable *)(env_lst->content))->value));
		env_lst = env_lst->next;
	}
	return (NULL);

}

t_list *init_env(char **env)
{
	t_list		*env_lst;
	int			i;

	env_lst = NULL;
	i = 0;
	while (env[i])
	{
		ft_envlst_add_back(&env_lst, ft_lstnew(write_variable(env[i])));
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