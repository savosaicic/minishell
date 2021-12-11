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
    else if (!ft_strcmp(cmd_name, ":"))
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

void wait_all_pids()
{
	int status;
	int pid_ret;

	pid_ret = 1;
    prg->exit_status = 0;
	while (pid_ret > 0)
	{
		pid_ret = wait(&status);
		if (WIFEXITED(status))
            prg->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
            prg->exit_status = WTERMSIG(status);
	}
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

void	*xxmalloc(size_t size)
{
	void	*result;

	result = malloc(size);
	if (result == NULL)
		exit(1);
	return (result);
}

void	print_token(t_list *list)
{
	char **types = ft_split("UNIDENTIFIED WORD REDIRECT DGREAT DLESS PIPE ASSIGN", ' ');

	printf("\n");
	while (list)
	{
		printf("[%s:%s]  ", types[((t_token *)list->content)->token_type], ((t_token *)list->content)->token);
		list = list->next;
	}
	printf("\n");
	printf("__________________________\n\n");
	free_tab(types);
}

int		ft_close(int fd)
{
	if (fd > 0)
		close(fd);
	return (-1);
}

int		is_line_empty(char *line)
{
	int	i;

	i = 1;
	while (*line)
	{
		if (!is_space(*line))
			i = 0;
		line++;
	}
	return (i);
}