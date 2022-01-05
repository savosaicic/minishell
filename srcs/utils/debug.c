/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2022/01/01 15:33:43 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_list *list)
{
	char	**types;

	types = ft_split(
			"UNIDENTIFIED WORD REDIRECT DGREAT DLESS PIPE ASSIGN", ' ');
	printf("\n");
	while (list)
	{
		printf("[%s:%s]  ", types[((t_token *)list->content)->token_type],
			((t_token *)list->content)->token);
		list = list->next;
	}
	printf("\n");
	printf("__________________________\n\n");
	free_tab(types);
}

void	print_cmd_lst(t_list *cmd_lst)
{
	int	i;

	while (cmd_lst)
	{
		printf("[");
		i = 0;
		while (((t_cmd *)cmd_lst->content)->args[i])
			printf("%s; ", ((t_cmd *)cmd_lst->content)->args[i++]);
		printf("]\n");
		printf("#############################\n");
		cmd_lst = cmd_lst->next;
	}
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		fflush(stdin);
		i++;
	}
}
