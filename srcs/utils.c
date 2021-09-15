#include "minishell.h"

void	print_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		// printf("%s\n", tab[i]);
		fflush(stdin);
		i++;;
	}
	printf("len tab %d\n", i);
	fflush(stdin);
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
