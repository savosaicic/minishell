#include "minishell.h"

int     is_builtin(char *cmd_name)
{
    if (!ft_strcmp(cmd_name, "echo"))
        return (1);
    else if (!ft_strcmp(cmd_name, "cd"))
        return (1);
    else if (!ft_strcmp(cmd_name, "pwd"))
        return (1);
    else if (!ft_strcmp(cmd_name, "export"))
        return (1);
    else if (!ft_strcmp(cmd_name, "unset"))
        return (1);
    else if (!ft_strcmp(cmd_name, "env"))
        return (1);
    else if (!ft_strcmp(cmd_name, "exit"))
        return (1);
    else if (!ft_strcmp(cmd_name, "env"))
        return (1);
    return (0);
}

int     is_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
        || c == '\v' || c == '\f')
        return (1);
    return (0);
}

void	ft_lstadd_back2(t_list **alst, t_list *new)
{
	t_list	*last;
	t_list	*current;


	(void)current;
	(void)last;
	if (alst)
	{
		current = *alst;
		if (current)
		{
//			printf("env_lst %s\n", CAST(current, t_variable*)->name);
			// last = ft_lstlast(*alst);
			// last->next = new;
			current = current->next;
		}
		else
			*alst = new;
	}
}
