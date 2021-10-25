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

void	ft_envlst_add_back(t_list **alst, t_list *new)
{
	t_list	*last;

	if (alst)
	{
		if (*alst)
		{
			last = ft_lstsearch(*alst, new);
            if (!last)
            {
                last = ft_lstlast(*alst);   
			    last->next = new;
            }
            else
            {
                ((t_variable *)last->content)->value = ((t_variable *)new->content)->value;
            }
		}
		else
			*alst = new;
	}
}

t_list    *ft_lstsearch(t_list *lst, t_list *search)
{
	t_list	*prev;

	prev = NULL;
	while (lst)
	{
		prev = lst;
        if (!ft_strcmp(((t_variable *)lst->content)->name, ((t_variable *)search->content)->name))            
            return (prev);
		lst = lst->next;
	}
	return (NULL);
}