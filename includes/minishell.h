#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#ifdef __APPLE__
	# define rl_clear_history clear_history
#endif

#define CAST(var, type) ((type)var->content)

#include "libft.h"
#include "structures.h"

t_list		*parse_tokens(t_list *token_lst);

t_list		*get_token(char *cmd_buffer);
t_ttype		get_token_type(char *token);
int			handle_quote(char **cmd_buffer, char *str, t_list **token_lst);
int			handle_pipe_and_redirection(char **cmd_buffer, t_list **token_lst);
t_token	*init_token_struct(char *token);

char		*search_in_tab(char **env, char *var);
char    	**get_path(char **envp);
char    	*get_cmd_path(char **path, char *cmd);

void	exit_failure(t_prg *prg, t_cmd *cmd, char *error_msg, int status);
int		write_error_msg(char *bin_name, char *item_name, char *error_msg);

int		exec_cmd(t_prg *prg, t_cmd *cmd);

void	clear_cmd_struct(void *cmd_struct);
void	clear_token_struct(void *token_struct);
void	print_tab(char **tab);
void	free_tab(char **tab);
#endif
