#include "minishell.h"

t_prg	*init_shell(char **env)
{
	t_prg	*prg;
	char	*pwd;

	prg = malloc(sizeof(t_prg));
	if (!prg)
		exit_failure(prg, NULL, "sh: insufficient memory", 1);
	pwd = search_in_tab(env, "PWD=");
	prg->env = env;
	prg->pwd = ft_strdup(pwd + ft_strlen("PWD="));
	if (prg->pwd == NULL)
		exit_failure(prg, NULL, "sh: insufficient memory", 1);
	prg->env_lst = init_env(env);
	prg->cmd_buffer = NULL;
	prg->home_path = ft_strdup((((t_variable *)(ft_lstsearch(prg->env_lst, "HOME")->content))->value));
	prg->last_exit_status = 0;
	return (prg);
}

t_list *get_command_lst(t_prg *prg)
{
	t_list *token_lst;
	t_list *cmd_lst;

	cmd_lst = NULL;
	add_history(prg->cmd_buffer);
	token_lst = get_token(prg, prg->cmd_buffer);
//	if (token_lst == NULL)
//		exit_failure(prg, NULL, "sh: insufficient memory", 1);
	cmd_lst = parse_tokens(prg, token_lst);
	ft_lstclear(&token_lst, clear_token_struct);
	return (cmd_lst);
}

void	execute_cmd_list(t_prg *prg, t_list *cmd_lst)
{
	pid_t	pid;
	int		status;
	t_list	**head;
	int		cmd_num;
	int 	ret;
	t_io	io_struct;
	int		i;

	head = &cmd_lst;
	cmd_num = ft_lstsize(cmd_lst);
	io_struct = init_io_struct();
	if (prg->cmds_len == 1 && is_builtin(((t_cmd *)cmd_lst->content)->args[0]) == 1)
	{
		((t_cmd *)cmd_lst->content)->path = write_command(prg, ((t_cmd *)cmd_lst->content)->args);
		prg->last_exit_status = execute(prg, cmd_lst->content);
		ft_lstclear(head, clear_cmd_struct);
		return ;
	}
	i = 0;
	while (i < cmd_num)
	{
		dup2(io_struct.fdin, STDIN_FILENO);
		close(io_struct.fdin);
		if (i == cmd_num - 1)
			io_struct = set_fd_last_cmd(((t_cmd *)(cmd_lst->content)), io_struct);
		else
			io_struct = set_fds(((t_cmd *)(cmd_lst->content)), io_struct);
		dup2(io_struct.fdout, STDOUT_FILENO);
		close(io_struct.fdout);
		pid = fork();
		if (!pid)
		{
			((t_cmd *)cmd_lst->content)->path = write_command(prg, ((t_cmd *)cmd_lst->content)->args);
			ret = execute(prg, cmd_lst->content);
			exit_success(prg, ret);
			exit(ret);
		}
		cmd_lst = cmd_lst->next;
		i++;
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		prg->last_exit_status = WEXITSTATUS(status);
	restore_and_close_fds(io_struct);
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
		{
			cmd_lst = get_command_lst(prg);
			prg->cmds_len = ft_lstsize(cmd_lst);
		}
		if (cmd_lst)
			//execute_cmd_list(prg, cmd_lst);
		free(prg->cmd_buffer);
	}
	return (0);
}