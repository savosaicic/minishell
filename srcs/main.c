#include "minishell.h"

void init_shell(t_prg *prg, char **env)
{
	char *pwd;

	pwd = search_in_tab(env, "PWD=");
	prg->pwd = ft_strdup(pwd + ft_strlen("PWD="));
	prg->env = env;
	prg->cmd_buffer = NULL;
	if (prg->pwd == NULL)
		exit_failure(prg, "sh: insufficient memory", 1);
}

t_list 	*get_command_lst(t_prg *prg)
{
	t_list		*token_lst;
	t_list		*cmd_lst;

	prg->cmd_buffer = readline("$> ");
	if (!prg->cmd_buffer)
		exit_success(prg, 0);
	add_history(prg->cmd_buffer);
	token_lst = get_token(prg->cmd_buffer);
	if (token_lst == NULL)
		exit_failure(prg, "sh: insufficient memory", 1);
	cmd_lst = parse_tokens(prg, token_lst);
	ft_lstclear(&token_lst, clear_token_struct);
	free(prg->cmd_buffer);
	return (cmd_lst);
}

int wait_all_pids(void)
{
	int			ret;
	int			status;
	int			pid_ret;

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

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_prg		prg;
	t_list		*cmd_lst;
	pid_t		pid;
	int			status;
	int			ret;

	init_shell(&prg, env);
	int debug = 0;
	while (1)
	{
		cmd_lst = get_command_lst(&prg);
		while (cmd_lst)
		{
			pid = fork();
			if (!pid)
			{
				((t_cmd *)cmd_lst->content)->path = write_command(&prg, ((t_cmd *)cmd_lst->content)->args);
				ret = execute(&prg, cmd_lst);
				exit(ret);
			}
			ret = 0;
			waitpid(ret, &status, 0);
			if (WIFEXITED(status))
				ret = WEXITSTATUS(status);
			cmd_lst = cmd_lst->next;
		}
		ft_lstclear(&cmd_lst, clear_cmd_struct);
		debug++;
	}
	return (0);
}
