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
		prg->env = env;
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

t_io set_file_descriptors(t_list **cmd_lst, t_io io_struct, int cmds_len, int *is_first)
{
	if (cmds_len == 1)
		io_struct = set_fd_last_cmd(cmd_lst, io_struct, is_first);
	else
		io_struct = set_fds(cmd_lst, io_struct, is_first);
	return (io_struct);
}


t_io set_and_execute_command(t_list **cmd_lst, t_io io_struct, int cmds_len, int *is_first)
{
	int ret;

	prg->pid = 0;
	io_struct = set_file_descriptors(cmd_lst, io_struct, cmds_len, is_first);
	if (!is_builtin(((t_cmd *)(*cmd_lst)->content)->args[0]))
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
		dup2(((t_cmd *)(*cmd_lst)->content)->fdin, STDIN_FILENO);
		dup2(((t_cmd *)(*cmd_lst)->content)->fdout, STDOUT_FILENO);

		close(((t_cmd *)(*cmd_lst)->content)->fdout);
		close(((t_cmd *)(*cmd_lst)->content)->fdin);

		close(io_struct.close_in_child);

		((t_cmd *)(*cmd_lst)->content)->path = write_command(((t_cmd *)(*cmd_lst)->content)->args);
		ret = execute((*cmd_lst)->content);
		if (!is_builtin(((t_cmd *)(*cmd_lst)->content)->args[0]))
			exit_success(ret, FALSE);
	}
	else
	{
		close(io_struct.close_in_parent);
		close(((t_cmd *)(*cmd_lst)->content)->fdout);
		close(((t_cmd *)(*cmd_lst)->content)->fdin);
	}
	return (io_struct);
}

void	execution_manager(t_list *cmd_lst)
{
	t_io	io_struct;
	int		cmds_len;

	cmds_len = ft_lstsize(cmd_lst);
	io_struct = init_io_struct();
	prg->cmd_lst = cmd_lst;
	prg->cmds_len = cmds_len;

	int	is_first = 1;
	while (cmds_len)
	{
		io_struct = set_and_execute_command(&cmd_lst, io_struct, cmds_len, &is_first);
		cmd_lst = cmd_lst->next;
		cmds_len--;
	}
	restore_and_close_fds(io_struct);
	if (prg->child)
		wait_all_pids();
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
			ft_exit(0, TRUE);
		else if (!is_rl_line_empty(rl_line_buffer))
			cmd_lst = get_command_lst();
		if (cmd_lst)
			execution_manager(cmd_lst);
		ft_lstclear(&cmd_lst, clear_cmd_struct);
	}
	return (0);
}