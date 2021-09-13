#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"

typedef enum	e_ttype
{
	UNIDENTIFIED,
	T_WORD,
	T_OPERATOR,
	T_PIPE
}				t_ttype;

typedef struct	s_cmd
{
	t_ttype			token_type;
	char			*token;
	struct s_cmd	*next;
}				t_cmd;

void	print_list(t_cmd *list);
t_cmd	*new_node(char *token);
int		lst_size(t_cmd	*head);
t_cmd	*get_last_node(t_cmd *head);
void	delete_list(t_cmd **head);
void	push_front(t_cmd **head, t_cmd *new_node);
void	push_back(t_cmd **head, t_cmd *new_node);

t_cmd	*get_token(char *cmd_buffer);
t_ttype	get_token_type(char *token);

#endif
