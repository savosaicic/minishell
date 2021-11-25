#include "minishell.h"

int     is_builtin(char *cmd_name)
{
    if (!ft_strcmp(cmd_name, "echo"))
        return (1);
    else if (!ft_strcmp(cmd_name, "cd"))
        return (1);
    else if (!ft_strcmp(cmd_name, "pwd"))
        return (1);
    else if (!ft_strcmp(cmd_name, "export"))
        return (1);
    else if (!ft_strcmp(cmd_name, "unset"))
        return (1);
    else if (!ft_strcmp(cmd_name, "env"))
        return (1);
    else if (!ft_strcmp(cmd_name, "exit"))
        return (1);
    else if (!ft_strcmp(cmd_name, "env"))
        return (1);
    return (0);
}

int     is_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
        || c == '\v' || c == '\f')
        return (1);
    return (0);
}

int wait_all_pids(void)
{
	int ret;
	int status;
	int pid_ret;

	pid_ret = 1;
	ret = 0;
	while (pid_ret > 0)
	{
		pid_ret = wait(&status);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			ret = WTERMSIG(status);
		else
			ret = 1;
	}
	return (ret);
}

int	ft_charlen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	is_redirect(char c)
{
	return (c == '<' || c == '>');
}

int	is_pipe(char c)
{
	return (c == '|');
}

void	skip_spaces(char **str)
{
	if (!str)
		return ;
	while (**str == ' ')
		(*str)++;
}

void	*xmalloc(size_t size)
{
	void	*result;

	result = malloc(size);
	if (result == NULL)
		exit(1);
	return (result);
}