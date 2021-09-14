#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"
#include "structures.h"

void	print_list(t_tokenlst *list);
t_tokenlst	*new_node(char *token);
int		lst_size(t_tokenlst	*head);
t_tokenlst	*get_last_node(t_tokenlst *head);
void	delete_list(t_tokenlst **head);
void	push_front(t_tokenlst **head, t_tokenlst *new_node);
void	push_back(t_tokenlst **head, t_tokenlst *new_node);
t_list	*parse_tokens(t_tokenlst *head);

t_tokenlst	*get_token(char *cmd_buffer);
t_ttype	get_token_type(char *token);

#endif
