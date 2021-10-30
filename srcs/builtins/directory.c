#include "minishell.h"

int pwd(t_cmd *cmd)
{
	char *buf;

	(void)cmd;
	buf = NULL;
	buf = malloc(sizeof(*buf) * 400);
	if (!buf)
		return (write_error_msg("minishell", strerror(errno), NULL, 1));
	if (!getcwd(buf, 100))
	{
		free(buf);
		return (write_error_msg("minishell", strerror(errno), NULL, 1));
	}
	printf("%s\n", buf);
	free(buf);
	return (0);
}

int cd(t_cmd *cmd, t_list *env_lst)
{
	(void)cmd;
	char *tmp;

	if (!cmd->args[1])
		return (0);
	else if (ft_charlen(cmd->args) > 2)
		return (write_error_msg("minishell", "too many arguments", NULL, 1));
	if (cmd->args[1][0] == '~')
		tmp = ft_getenv(env_lst, "HOME");
	else
		tmp = ft_strdup(cmd->args[1]);
	if (chdir(tmp) == -1)
	{
		free(tmp);
		return (write_error_msg("minishell", cmd->args[1], strerror(errno), 1));
	}
	free(tmp);
	return (0);
}