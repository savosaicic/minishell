#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef enum	e_ttype
{
	UNIDENTIFIED,
	T_WORD,
	T_OPERATOR,
	T_PIPE
}				t_ttype;

typedef struct	s_token
{
	t_ttype			token_type;
	char			*token;
}				t_token;

typedef struct s_cmd
{
	char	**args;
	char	*path;
	int		fd[2];
}				t_cmd;

typedef struct s_prg
{
	char	*pwd;
	char 	**env;
}				t_prg;

#endif
