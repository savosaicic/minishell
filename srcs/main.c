#include "minishell.h"

t_prg	*prg;

t_prg	*init_shell(char **env)
{
	prg = malloc(sizeof(*prg));
	if (!prg)
		exit_failure(NULL, "insufficient memory", 1);
	if (!*env)
	{
		prg->env = xmalloc(sizeof(*prg->env));
		*prg->env = NULL;
	}
	else
	{
		prg->env = env;
	}
	// printf("env %s\n", prg->env[0]);
	prg->env_lst = init_env();
	prg->pwd = ft_getenv(prg->env_lst, "PWD");
	prg->home_path = ft_getenv(prg->env_lst, "HOME");
	rl_line_buffer = NULL;
	prg->exit_status = 0;
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
		exit_failure(NULL, "insufficient memory", 1);
	cmd_lst = parse_tokens(token_lst);
	ft_lstclear(&token_lst, clear_token_struct);
	if (!cmd_lst)
		ft_lstclear(&cmd_lst, clear_cmd_struct);
	return (cmd_lst);
}

t_io plug_pipe(t_list *cmd_lst, t_io io_struct, int cmds_len)
{
	dup2(io_struct.fdin, STDIN_FILENO);
	close(io_struct.fdin);
	if (cmds_len == 1)
		io_struct = set_fd_last_cmd(((t_cmd *)(cmd_lst->content)), io_struct);
	else
		io_struct = set_fds(((t_cmd *)(cmd_lst->content)), io_struct);

	dup2(io_struct.fdout, STDOUT_FILENO);
	close(io_struct.fdout);
	return (io_struct);
}


void set_and_execute_command(t_list *cmd_lst, t_io io_struct, int cmds_len)
{
	int ret;

	prg->pid = 0;

	io_struct = plug_pipe(cmd_lst, io_struct, cmds_len);
	if (!is_builtin(((t_cmd *)cmd_lst->content)->args[0]))
	{
		prg->child = TRUE;
		prg->pid = fork();
	}
	if (ft_strchr(rl_line_buffer, '|'))
	{
		prg->child = TRUE;
	}
	if (!prg->pid)
	{
		// printf("env %s\n", prg->env[0]);
		((t_cmd *)cmd_lst->content)->path = write_command(((t_cmd *)cmd_lst->content)->args);
		ret = execute(cmd_lst->content);
		if (!is_builtin(((t_cmd *)cmd_lst->content)->args[0]))
			exit_success(ret, FALSE);
	}
}

void	execution_manager(t_list *cmd_lst)
{
	t_list	**head_cmd_lst;
	t_io	io_struct;
	int		cmds_len;

	head_cmd_lst = &cmd_lst;
	cmds_len = ft_lstsize(cmd_lst);
	io_struct = init_io_struct();
	while (cmds_len)
	{
		set_and_execute_command(cmd_lst, io_struct, cmds_len);
		cmd_lst = cmd_lst->next;
		cmds_len--;
	}
	wait_all_pids();
	restore_and_close_fds(io_struct);
	ft_lstclear(head_cmd_lst, clear_cmd_struct);
}

int	main(int ac __attribute__((unused)), char **av __attribute__((unused)), char **env)
{
	t_list	*cmd_lst;

	init_shell(env);	
	watch_signals();
	while (1)
	{
		cmd_lst = NULL;
		prg->child = FALSE;
		rl_line_buffer = readline("$> ");
		if (!rl_line_buffer)
			exit_success(0, TRUE);
		else if (ft_strlen(rl_line_buffer))
			cmd_lst = get_command_lst();
		if (cmd_lst)
			execution_manager(cmd_lst);
	}
	return (0);
}