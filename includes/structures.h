/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasaicic <sasaicic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:09:46 by sasaicic          #+#    #+#             */
/*   Updated: 2021/12/27 15:35:06 by sasaicic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef enum	e_ttype
{
	UNIDENTIFIED,
	T_WORD,
	T_REDIRECT,
	T_DGREAT,
	T_DLESS,
	T_PIPE,
	T_ASSIGN
}				t_ttype;

typedef struct	s_token
{
	t_ttype			token_type;
	char			*token;
}				t_token;

typedef struct s_cmd
{
	bool	is_builtin;
	char	**args;
	char	*path;
	int		r_io[2]; //array of 2 int to store respectively: INPUT and OUTPUT fds (For redirection)

	int		fdin;
	int		fdout;
	bool	is_first;
}				t_cmd;

typedef struct	s_io
{
	int	fds[2]; 
	int	save_stdin;
	int	save_stdout;
	int fdin;
	int	fdout;

	int	close_in_child;
	int	close_in_parent;

	int	next_fdin;

	int	last_close[64];
}				t_io;

typedef struct s_prg
{
	pid_t 	pid;
	char	*pwd;
	bool	child;
	char 	**env;
	t_list	*env_lst;
	t_list	*cmd_lst;
	char	*cmd_buffer;
	int		exit_status;
	int		cmds_len;
	char	*home_path;
	bool	in_heredoc;
	bool	sig_int;
	int		save_stdin;
}				t_prg;

typedef struct	s_variable
{
	char	*name;
	char	*value;
}				t_variable;

#endif
