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

/*builtin*/
int export(t_cmd *cmd, t_list *env_lst);
int unset(t_cmd *cmd, t_list *env_lst);
int	echo(t_cmd *cmd);
int	print_env(t_list *env_lst, char *str);
int		pwd(t_cmd *cmd);
int cd(t_cmd *cmd, t_list *env_lst);
int exit_shell
(t_prg *prg, t_cmd *cmd);

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

/*execute*/
int    	execute_builtin(t_prg *prg, t_cmd *cmd);
int		execute_command(t_prg *prg, t_cmd *cmd);
int     execute(t_prg *prg, t_cmd *cmd);

/*piping*/
t_io	set_fds(t_cmd *cmd, t_io io_struct);
t_io	set_fd_last_cmd(t_cmd *cmd, t_io io_struct);
t_io	init_io_struct(void);
void	restore_and_close_fds(t_io io_struct);

/*utils*/
void	clear_prg_struct(t_prg *prg);
void	clear_token_struct(void *token_struct);
void	clear_cmd_struct(void *cmd_struct);
void	clear_var_struct(void *var_struct);
int		ft_charlen(char **tab);

void	print_tab(char **tab);
void	free_tab(char **tab);
void	exit_success(t_prg *prg, int status);
int     is_space(char c);


int     is_builtin(char *cmd_name);
int     wait_all_pids(void);

void	ft_lstadd_back2(t_list **alst, t_list *new);
t_list  *ft_lstsearch(t_list *lst, char *search);

void	ft_envlst_add_back(t_list **alst, t_list *new);

#endif