#include "minishell.h"

static char		*get_cmd_path(char **paths, char *cmd, char *pwd)
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
}

char	*write_command(t_prg *prg, char **cmd)
{
	char **paths;
	char *path;

	paths = ft_split(search_in_tab(prg->env, "PATH=") + ft_strlen("PATH="), ':');
	path = get_cmd_path(paths, cmd[0], prg->pwd);
	free_tab(paths);
	return (path);
}