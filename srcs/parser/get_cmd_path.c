#include "minishell.h"

char	*get_cmd_path(char **path, char *cmd)
{
	char	*cmd_path;
	int		ret;
	int		i;

	ret = 1;
	i = 1;
	cmd_path = ft_strjoin(path[i - 1], cmd);
	if (cmd_path == NULL)
		return (NULL);
	while (ret != 0 && path[i] != NULL)
	{
		free(cmd_path);
		cmd_path = ft_strjoin(path[i], cmd);
		ret = access(cmd_path, X_OK);
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