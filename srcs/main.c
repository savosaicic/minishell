#include "minishell.h"

t_prg	*init_shell(char **env)
{
	t_prg	*prg;
	char	*pwd;

	prg = malloc(sizeof(t_prg));
	if (!prg)
		exit_failure(prg, NULL, "sh: insufficient memory", 1);

	pwd = search_in_tab(env, "PWD=");
	prg->pwd = ft_strdup(pwd + ft_strlen("PWD="));
	prg->env = env;
	prg->env_lst = init_env(env);
	prg->cmd_buffer = NULL;
	if (prg->pwd == NULL)
		exit_failure(prg, NULL, "sh: insufficient memory", 1);
	return (prg);
}

t_list *get_command_lst(t_prg *prg)
{
	t_list *token_lst;
	t_list *cmd_lst;

	cmd_lst = NULL;
	add_history(prg->cmd_buffer);
	token_lst = get_token(prg, prg->cmd_buffer);
	if (token_lst == NULL)
		exit_failure(prg, NULL, "sh: insufficient memory", 1);
	cmd_lst = parse_tokens(prg, token_lst);
	ft_lstclear(&token_lst, clear_token_struct);
	return (cmd_lst);
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

void	execute_cmd_list(t_prg *prg, t_list *cmd_lst)
{
	pid_t	pid;
	int		ret;
	int		status;
	t_list	**head;

	head = &cmd_lst;
	while (cmd_lst)
	{
		pid = fork();
		if (!pid)
		{
			((t_cmd *)cmd_lst->content)->path = write_command(prg, ((t_cmd *)cmd_lst->content)->args);
			// if (!((t_cmd *)cmd_lst->content)->path)
			// 	write_error_msg("minishell", ((t_cmd *)cmd_lst->content)->args[0], "command not found");
			// else
			// {
				ret = execute(prg, cmd_lst->content);
				exit_success(prg, ret);
			// }
			exit(ret);
		}
		ret = 0;
		waitpid(ret, &status, 0);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
		cmd_lst = cmd_lst->next;
	}
	ft_lstclear(head, clear_cmd_struct);
}

int	main(int ac __attribute__((unused)), char **av __attribute__((unused)), char **env)
{
	t_prg	*prg;
	t_list	*cmd_lst;

	prg = init_shell(env);
	while (1)
	{
		cmd_lst = NULL;
		prg->cmd_buffer = readline("$> ");
		if (!prg->cmd_buffer)
			exit_success(prg, 0);
		else if (ft_strlen(prg->cmd_buffer))
			cmd_lst = get_command_lst(prg);
		if (cmd_lst)
			execute_cmd_list(prg, cmd_lst);
		free(prg->cmd_buffer);
	}
	return (0);
}