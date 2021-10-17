#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>

#include "libft.h"
#include "structures.h"

#ifdef __APPLE__
	# define rl_clear_history clear_history
#endif

# define TRUE 1
# define FALSE 0

# define CAST(var, type) ((type)var->content)

int			handle_quote(char **cmd_buffer, char *str, t_list **token_lst);
int			handle_pipe_and_redirection(char **cmd_buffer, t_list **token_lst);
int			parse_redirection(t_cmd **cmd, t_list **token_lst);
char		*handle_expansion(char **cmd_buffer, char **save, t_list **token_lst, t_list *env_lst);
char		*ft_getenv(t_list *env_lst, char *var_search);

char    	**get_path(char **envp);
char    	*get_cmd_path(char **path, char *cmd);

void		exit_failure(t_prg *prg, t_cmd *cmd, char *error_msg, int status);
int			write_error_msg(char *bin_name, char *item_name, char *error_msg, int status);


/*lexer*/
t_list	*parse_tokens(t_prg *prg, t_list *token_lst);
t_ttype	get_token_type(char *token);
t_list	*get_token(t_prg *prg, char *cmd_buffer);
t_token	*write_token(char *token);

/*parser*/
char *clean_command_line(char *line_buff);
t_list *init_env(char **env);
t_variable *write_variable(char *var);
void add_var_in_env(char *variable, t_list *env_lst);



/*command*/
char	*search_in_tab(char **env, char *var);
char	*write_command(t_prg *prg, char **cmd);

/*builtin*/
int	echo(t_cmd *cmd);
int export(t_cmd *cmd, t_list *env_lst);
int	env(t_list *env_lst);



/*execute*/
int    execute_builtin(t_prg *prg, t_cmd *cmd);
int	execute_command(t_prg *prg, t_cmd *cmd);
int     execute(t_prg *prg, t_cmd *cmd);

/*utils*/
void	clear_prg_struct(t_prg *prg);
void	clear_token_struct(void *token_struct);
void	clear_cmd_struct(void *cmd_struct);
void	print_tab(char **tab);
void	free_tab(char **tab);
void	exit_success(t_prg *prg, int status);
int     is_space(char c);


int     is_builtin(char *cmd_name);
int     wait_all_pids(void);
void	print_variables(t_list *lst);


#endif
