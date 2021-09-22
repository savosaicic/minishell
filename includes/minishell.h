#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

#include "libft.h"
#include "structures.h"

/*lexer*/
t_list	*parse_tokens(t_prg *prg, t_list *token_lst);
t_ttype	get_token_type(char *token);
t_list	*get_token(char *cmd_buffer);

/*parser*/
char *clean_command_line(char *line_buff);


/*command*/
char	*search_in_tab(char **env, char *var);
char	*write_command(t_prg *prg, char **cmd);

/*builtin*/
void	echo(t_cmd *cmd);

/*execute*/
void    execute_builtin(t_prg *prg, t_cmd *cmd);
void	execute_command(t_prg *prg, t_cmd *cmd);
int     execute(t_prg *prg, t_list *cmd_lst);

/*utils*/
void	clear_token_struct(void *token_struct);
void	clear_cmd_struct(void *cmd_struct);
void	print_tab(char **tab);
void	free_tab(char **tab);
void	exit_failure(t_prg *prg, char *str, int status);
void	exit_success(t_prg *prg, int status);

int     is_builtin(char *cmd_name);
int     wait_all_pids(void);

#endif
