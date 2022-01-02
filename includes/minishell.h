/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:09:46 by sasaicic          #+#    #+#             */
/*   Updated: 2022/01/02 16:29:24 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>
# include <signal.h>
# include <dirent.h>
# include "libft.h"
# include "structures.h"

# define TRUE 1
# define FALSE 0
# define MAX_TOKEN_SIZE 256 
# define MAX_PIPE 64

extern t_prg	*g_prg;

t_variable	*write_variable(char *var);
t_list		*init_env(void);

char		*handle_quote(t_list **token_lst, char **cmd_buffer, char *str);
char		*handle_expansion(t_prg *g_prg, char **cmd_buffer, char **save,
				t_list **token_lst);
char		*ft_getenv(t_list *env_lst, char *var_search);
char		*perform_expansion(t_prg *g_prg, t_list *env_lst,
				char **cmd_buffer);

char		**get_path(void);
char		*get_cmd_path(char **path, char *cmd);

void		exit_failure(char *item_name, char *error_msg, int status);
int			puterror(char *item_name, char *error_msg, int status);

/*builtin*/
int			export(t_cmd *cmd, t_list *env_lst);
int			unset(t_cmd *cmd, t_list *env_lst);
int			echo(t_cmd *cmd);
int			print_env(t_list *env_lst, char *str);
int			pwd(t_cmd *cmd);
int			cd(t_cmd *cmd, char *home_math);
int			exit_shell(t_cmd *cmd, char *exit_str);
void		ft_close(int *fd);
int			do_nothing(void);

/*lexer*/
int			handle_pipe_and_redirection(char **cmd_buffer, t_list **token_lst);
t_list		*parse_tokens(t_list *token_lst);
t_ttype		get_token_type(char *token);
t_list		*get_token(char *cmd_buffer);
t_token		*write_token(char *token);
int			lex_expansion(t_list **token_lst, char **cmd_buffer, char **buffer);
int			lex_quotes(t_list **token_lst, char **cmd_buffer, char **buffer);
int			lex_operators(t_list **token_lst, char **cmd_buffer, char **buffer);
int			lex_spaces(t_list **token_lst, char **cmd_buffer, char **buffer);
int			lex_chars(int i, char **cmd_buffer, char **buffer);
int			check_token(t_list *token_lst);

/*parser*/
char		*clean_command_line(char *line_buff);
void		add_var_in_env(char *variable, t_list *env_lst);
void		parse_heredoc(t_list **token_lst, t_cmd **cmd);
int			parse_redirection(t_list **token_lst, t_cmd **cmd, int *i);
void		parse_pipe(t_list **token_lst, t_cmd **cmd, t_list **cmd_lst,
				int *i);
t_cmd		*init_cmd_struct(int args_num, bool is_first);
void		parse_argument(t_list **token_lst, t_cmd **cmd, int *i);
void		add_last_cmd(t_cmd **cmd, t_list **cmd_lst, int i);
int			is_token_in_list(t_list *token_lst, t_ttype type);

/*command*/
char		*search_in_tab(char **env, char *var);
char		*write_command(char **cmd);

/*execute_command*/
t_io		set_and_execute_command(t_list **cmd_lst, t_io io_struct,
				int cmds_len, int *is_first);
int			execute_builtin(t_cmd *cmd);
int			execute_command(t_cmd *cmd);
int			execute(t_cmd *cmd);

/*piping*/
t_io		set_fds(t_list **cmd_lst, t_io io_struct, int *is_first_cmd);
t_io		set_fd_last_cmd(t_list **cmd_lst, t_io io_struct,
				int *is_first_cmd);
t_io		init_io_struct(void);
void		restore_and_close_fds(t_io io_struct);
void		restore_and_close_fds2(t_io io_struct);

/*utils*/
void		clear_prg_struct(void);
void		clear_token_struct(void *token_struct);
void		clear_cmd_struct(void *cmd_struct);
void		clear_var_struct(void *var_struct);
int			ft_charlen(char **tab);
int			is_redirect(char c);
int			is_pipe(char c);
void		skip_spaces(char **str);
void		*xxmalloc(size_t size);
void		print_token(t_list *list);
void		print_cmd_lst(t_list *cmd_lst);

void		print_tab(char **tab);
void		free_tab(char **tab);
void		exit_success(int status, bool display);
int			is_space(char c);
int			is_line_empty(char *line);
void		print_cmd_lst(t_list *cmd_lst);
int			check_quote_and_forbiden_char(char *buffer);

int			is_builtin(char *cmd_name);
void		wait_all_pids(void);

void		ft_lstadd_back2(t_list **alst, t_list *new);
t_list		*ft_lstsearch(t_list *lst, char *search);

void		ft_envlst_add_back(t_list **alst, t_list *new);

/* signal.c */
void		sig_int(int sig __attribute__((unused)));
void		sig_quit(int sig __attribute__((unused)));
void		watch_signals(void);

int			handle_heredoc(t_list **token_lst, t_cmd **cmd);
void		ft_exit(int status, bool display);
int			ft_onlychr(char *str, char c);
int			wait_pid(pid_t pid);

#endif
