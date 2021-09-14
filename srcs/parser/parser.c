#include "minishell.h"

<<<<<<< HEAD
char	*get_cmd_path(char **paths, char *cmd, char *pwd)
{
	int		i;
	char	*pwd_cmd;

	i = 0;
	while (paths[i])
	{
		pwd_cmd = ft_strdup(paths[i]);
		pwd_cmd = ft_memjoin(pwd_cmd, "/");
		pwd_cmd = ft_memjoin(pwd_cmd, cmd);
		if (access(pwd_cmd, F_OK) == 0)
			return (pwd_cmd);
		else
			free(pwd_cmd);
		i++;
	}
	if (cmd[0] != '/')
	{
		pwd_cmd = ft_strdup(pwd);
		pwd_cmd = ft_memjoin(pwd_cmd, "/");
		pwd_cmd = ft_memjoin(pwd_cmd, cmd);
	}
	else
		pwd_cmd = ft_strdup(cmd);
	return (pwd_cmd);
}

char	*search_in_tab(char **env, char *var)
{
	int		i;
	int		var_len;

	i = 0;
	var_len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, var_len) == 0)
			break ;
		i++;
	}
	return (env[i]);
=======
int		is_cmd_sep(t_ttype type){return (type == T_PIPE);}

/*
** t_list cmd_lst->content points to a t_cmd struct
*/

t_list	*parse_tokens(t_tokenlst *token_lst)
{
	t_list	*cmd_lst;
	t_cmd	*cmd;
	int		i;
	
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = (char **)malloc(sizeof(char *));
	if (!cmd->args)
		return (NULL);

	cmd_lst = NULL;

	i = 0;
	while (token_lst && !is_cmd_sep(token_lst->token_type))
	{
		cmd->args[i] = ft_strdup(token_lst->token);
		token_lst = token_lst->next;
		i++;

		if (!token_lst)
			ft_lstadd_back(&cmd_lst, ft_lstnew((void *)cmd));
		else if (is_cmd_sep(token_lst->token_type))
		{
			ft_lstadd_back(&cmd_lst, ft_lstnew((void *)cmd));
			if (token_lst)
			{
				token_lst = token_lst->next;
				cmd = (t_cmd *)malloc(sizeof(t_cmd));
				if (!cmd)
					return (NULL);
				cmd->args = (char **)malloc(sizeof(char *));
				if (!cmd->args)
					return (NULL);
			}
			i = 0;
		}
	}

	return (cmd_lst);
>>>>>>> get_cmd_list
}
