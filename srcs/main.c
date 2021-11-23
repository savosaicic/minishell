#include "minishell.h"

t_prg	*prg;

t_prg	*init_shell(char **env)
{
	t_prg	*prg;
	char	*pwd;

	prg = malloc(sizeof(t_prg));
	if (!prg)
		exit_failure(NULL, "sh: insufficient memory", 1);
	pwd = search_in_tab(env, "PWD=");
	prg->env = env;
	prg->pwd = ft_strdup(pwd + ft_strlen("PWD="));
	if (prg->pwd == NULL)
		exit_failure(NULL, "sh: insufficient memory", 1);
	prg->env_lst = init_env(env);
	rl_line_buffer = NULL;
	prg->home_path = ft_strdup((((t_variable *)(ft_lstsearch(prg->env_lst, "HOME")->content))->value));
	prg->last_exit_status = 0;
	return (prg);
}

t_list *get_command_lst(void)
{
	t_list *token_lst;
	t_list *cmd_lst;

	cmd_lst = NULL;
	add_history(rl_line_buffer);
	token_lst = get_token(rl_line_buffer);
	if (token_lst == NULL)
		exit_failure(NULL, "sh: insufficient memory", 1);
	cmd_lst = parse_tokens(token_lst);
	ft_lstclear(&token_lst, clear_token_struct);
	return (cmd_lst);
}

t_io plug_pipe(t_list *cmd_lst, t_io io_struct, int i, int cmd_num)
{
	dup2(io_struct.fdin, STDIN_FILENO);
	close(io_struct.fdin);
	if (i == cmd_num - 1)
		io_struct = set_fd_last_cmd(((t_cmd *)(cmd_lst->content)), io_struct);
	else
		io_struct = set_fds(((t_cmd *)(cmd_lst->content)), io_struct);
	dup2(io_struct.fdout, STDOUT_FILENO);
	close(io_struct.fdout);
	return (io_struct);
}


void execute_cmd(t_list *cmd_lst, t_io io_struct, int i, int cmd_num)
{
	int ret;

	prg->pid = 0;
	io_struct = plug_pipe(cmd_lst, io_struct, i, cmd_num);
	if (!is_builtin(((t_cmd *)cmd_lst->content)->args[0]))
		prg->pid = fork();
	if (!prg->pid)
	{
		unwatch_signals();
		((t_cmd *)cmd_lst->content)->path = write_command(((t_cmd *)cmd_lst->content)->args);
		ret = execute(cmd_lst->content);
		if (!is_builtin(((t_cmd *)cmd_lst->content)->args[0]))
			exit_success(ret);
	}
}

void	execute_cmd_list(t_list *cmd_lst)
{
	int		status;
	t_list	**head;
	int		cmd_num;
	t_io	io_struct;
	int		i;

	head = &cmd_lst;
	cmd_num = ft_lstsize(cmd_lst);
	io_struct = init_io_struct();
	i = 0;
	while (i < cmd_num)
	{
		execute_cmd(cmd_lst, io_struct, i, cmd_num);
		cmd_lst = cmd_lst->next;
		i++;
	}
	waitpid(prg->pid, &status, 0);
	if (WIFEXITED(status))
		prg->last_exit_status = WEXITSTATUS(status);
	restore_and_close_fds(io_struct);
	ft_lstclear(head, clear_cmd_struct);
}

int	main(int ac __attribute__((unused)), char **av __attribute__((unused)), char **env)
{
	t_list	*cmd_lst;

	prg = init_shell(env);	
	while (1)
	{
		cmd_lst = NULL;
		watch_signals();
		rl_line_buffer = readline("$> ");
		if (!rl_line_buffer)
		{
			ft_putstr_fd("exit\n", 1);
			exit_success(0);
		}
		else if (ft_strlen(rl_line_buffer))
		{
			cmd_lst = get_command_lst();
			prg->cmds_len = ft_lstsize(cmd_lst);
		}
		if (cmd_lst)
			execute_cmd_list(cmd_lst);
	}
	return (0);
}