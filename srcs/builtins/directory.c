#include "minishell.h"

int pwd(t_cmd *cmd)
{
	char *buf;

	(void)cmd;
	buf = NULL;
	buf = malloc(sizeof(*buf) * 400);
	if (!buf)
		return (puterror(strerror(errno), NULL, 1));
	if (!getcwd(buf, 100))
	{
		free(buf);
		return (puterror(strerror(errno), NULL, 1));
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}

int cd(t_cmd *cmd, char *home_path)
{
	(void)cmd;
	char *tmp;

	if (prg->child == TRUE)
		return (0);
	if (ft_charlen(cmd->args) > 2)
		return (puterror(NULL, "too many arguments", 1));
	if (!cmd->args[1] || cmd->args[1][0] == '~')
		tmp = home_path;
	else
		tmp = cmd->args[1];
	if (chdir(tmp) == -1)
		return (puterror(cmd->args[1], strerror(errno), 1));
	return (0);
}