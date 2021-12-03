#include "minishell.h"

char *get_cmd_path(char **path, char *cmd)
{
	char *cmd_path;
	int ret;
	int i;

	if (path == NULL)
		return (NULL);
	ret = 1;
	i = 1;
	cmd_path = ft_strjoin(path[i - 1], cmd);
	if (cmd_path == NULL)
		return (NULL);
	while (ret != 0 && path[i] != NULL)
	{
		free(cmd_path);
		cmd_path = ft_strjoin(path[i], cmd);
		ret = access(cmd_path, F_OK);
		i++;
	}
	if (ret == 0)
		return (cmd_path);
	else
	{
		free(cmd_path);
		return (NULL);
	}
}

char *search_in_tab(char **env, char *var)
{
	int i;
	int var_len;

	i = 0;
	var_len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, var_len) == 0)
			break;
		i++;
	}
	return (env[i]);
}

char *write_command(char **cmd)
{
	char	**paths;
	char	*cmd_path;

	paths = get_path();
	if (!ft_strchr(cmd[0], '/'))
		cmd_path = get_cmd_path(paths, cmd[0]);
	else
		cmd_path = ft_strdup(cmd[0]);
	free_tab(paths);
	return (cmd_path);
}