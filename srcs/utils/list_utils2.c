#include "minishell.h"

void	print_list(t_tokenlst *list)
{
	while (list)
	{
		printf("[%s](%d)  ", list->token, list->token_type);
		fflush(stdout);
		list = list->next;
	}
	ft_putchar('\n');
}
