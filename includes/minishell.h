#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stdbool.h>

#include "libft.h"
#include "structures.h"

t_list		*parse_tokens(t_list *token_lst);

t_list		*get_token(char *cmd_buffer);
t_ttype		get_token_type(char *token);

char		*search_in_tab(char **env, char *var);
char	*get_cmd_path(char **paths, char *cmd, char *pwd);


void	exit_failure(t_prg *prg, char *str, int status);

int		exec_cmd(t_prg *prg, t_cmd *cmd);

void	clear_cmd_struct(void *cmd_struct);
void	clear_token_struct(void *token_struct);
void	print_tab(char **tab);
void	free_tab(char **tab);
#endif
