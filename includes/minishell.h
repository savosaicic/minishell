#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

#include "libft.h"
#include "structures.h"

void		print_list(t_tokenlst *list);
t_tokenlst	*new_node(char *token);
int			lst_size(t_tokenlst	*head);
t_tokenlst	*get_last_node(t_tokenlst *head);
void		delete_list(t_tokenlst **head);
void		push_front(t_tokenlst **head, t_tokenlst *new_node);
void		push_back(t_tokenlst **head, t_tokenlst *new_node);
t_list		*parse_tokens(t_tokenlst *head);

t_tokenlst	*get_token(char *cmd_buffer);
t_ttype		get_token_type(char *token);

char		*search_in_tab(char **env, char *var);
char	*get_cmd_path(char **paths, char *cmd, char *pwd);


void	exit_failure(t_prg *prg, char *str, int status);

int		exec_cmd(t_cmd *cmd);

void	clear_cmd_struct(void *cmd_struct);
void	print_tab(char **tab);
void	free_tab(char **tab);
#endif
