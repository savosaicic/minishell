#include "minishell.h"

int print_env(t_list *env_lst, char *str)
{
	while (env_lst)
	{
		printf("%s%s=%s\n", str, ((t_variable *)env_lst->content)->name, ((t_variable *)env_lst->content)->value);
		env_lst = env_lst->next;
	}
	return (0);
}

int export(t_cmd *cmd, t_list *env_lst)
{
	int i;

	if (ft_charlen(cmd->args) <= 1)
		return (print_env(env_lst, "export "));
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

void delete_variable(t_list *env_lst, char *del)
{
	t_list *next;

	if (!ft_strcmp(((t_variable *)env_lst->content)->name, del))
	{
		*env_lst = *env_lst->next;
		return;
	}
	next = env_lst->next; // need to manage the last and the first
	while (next)
	{
		if (!ft_strcmp(((t_variable *)next->content)->name, del))
		{
			env_lst->next = next->next;
			// free(((t_variable *)next)->name);
			// free(((t_variable *)next)->value);
			// free(next);
			return;
		}
		env_lst = env_lst->next;
		next = next->next;
	}
}

int unset(t_cmd *cmd, t_list *env_lst)
{
	int i;
	int ret;

	ret = 0;
	if (ft_charlen(cmd->args) <= 1)
		return (write_error_msg("minishell", "unset", "not enough arguments", 1));
	if (cmd->args[1][0] == '-')
		return (write_error_msg("minishell", "-", "not a valid identifier", 1));
	i = 1;
	while (cmd->args[i])
	{
		if (ft_strchr(cmd->args[i], '/') || ft_strchr(cmd->args[i], '.'))
			ret = write_error_msg("minishell", "-", "not a valid identifier", 1);
		if (ft_lstsearch(env_lst, cmd->args[i]))
			delete_variable(env_lst, cmd->args[i]);
		i++;
	}
	return (ret);
}