/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colons.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:08:19 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/14 09:08:30 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_lst(t_list *cmd_lst)
{
	while (cmd_lst)
	{
		printf("[");
		for (int i=0; ((t_cmd *)cmd_lst->content)->args[i]; i++)
			printf("%s; ", ((t_cmd *)cmd_lst->content)->args[i]);
		printf("]\n");
		printf("#############################\n");
		cmd_lst = cmd_lst->next;
	}
}

int	do_nothing(void)
{
	return (0);
}
