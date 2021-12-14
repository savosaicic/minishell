#include "minishell.h"

void	print_token(t_list *list)
{
	char **types = ft_split("UNIDENTIFIED WORD REDIRECT DGREAT DLESS PIPE ASSIGN", ' ');

	printf("\n");
	while (list)
	{
		printf("[%s:%s]  ", types[((t_token *)list->content)->token_type], ((t_token *)list->content)->token);
		list = list->next;
	}
	printf("\n");
	printf("__________________________\n\n");
	free_tab(types);
}

void	print_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		fflush(stdin);
		i++;;
	}
}