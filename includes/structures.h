#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef enum	e_ttype
{
	UNIDENTIFIED,
	T_WORD,
	T_OPERATOR,
	T_PIPE
}				t_ttype;

typedef struct	s_tokenlst
{
	t_ttype			token_type;
	char			*token;
	struct s_tokenlst	*next;
}				t_tokenlst;

typedef struct s_cmd
{
	char	**args;
	char	*path;
	int		fd[2];
}				t_cmd;


#endif
