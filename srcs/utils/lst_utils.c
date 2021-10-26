#include "minishell.h"

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