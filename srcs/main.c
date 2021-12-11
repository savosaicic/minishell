#include "minishell.h"

t_prg	*prg;

t_prg	*init_shell(char **env)
{
	prg = malloc(sizeof(*prg));
	if (!prg)
		exit_failure(NULL, "insufficient memory", 1);
	if (!*env)
	{
		prg->env = xxmalloc(sizeof(*prg->env));
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

int		check_token(t_list *token_lst)
{
	int	is_first;

	is_first = 1;
	while (token_lst)
	{
		if ( ((t_token *)token_lst->content)->token_type == T_PIPE
			&& (ft_strlen(((t_token *)token_lst->content)->token) > 1 || !token_lst->next || is_first))
			return (puterror(NULL, "syntax error near unexpected token `|\'", -1));

		else if ( ((t_token *)token_lst->content)->token_type == T_REDIRECT
			&& (ft_strlen(((t_token *)token_lst->content)->token) > 2 || !token_lst->next))
			return (puterror("syntax error near unexpected token", ((t_token *)token_lst->content)->token, -1));
		token_lst = token_lst->next;
		is_first = 0;
	}

	return (0);
}

t_list *get_command_lst(char *cmd_buffer)
{
	t_list *token_lst;
	t_list *cmd_lst;

	cmd_lst = NULL;
	add_history(cmd_buffer);
	token_lst = get_token(cmd_buffer);


	if (token_lst == NULL)
		exit_failure(NULL, "insufficient memory", 1);

	if (check_token(token_lst) != -1)
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

		if (!is_builtin(((t_cmd *)(*cmd_lst)->content)->args[0]))
			close(io_struct.close_in_child);

		((t_cmd *)(*cmd_lst)->content)->path = write_command(((t_cmd *)(*cmd_lst)->content)->args);
		ret = execute((*cmd_lst)->content);
		if (!is_builtin(((t_cmd *)(*cmd_lst)->content)->args[0]))
			exit_success(ret, FALSE);
		else
		{
			dup2(io_struct.save_stdin, STDIN_FILENO);
			dup2(io_struct.save_stdout, STDOUT_FILENO);
		}
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
	char	*line = NULL;

	init_shell(env);
	watch_signals();
	while (1)
	{
		cmd_lst = NULL;
		prg->child = FALSE;
		free(line);
		line = NULL;
		line = readline("$> ");
		if (!line)
			ft_exit(0, TRUE);
		else if (!is_line_empty(line))
			cmd_lst = get_command_lst(line);
		if (cmd_lst)
			execution_manager(cmd_lst);
		ft_lstclear(&cmd_lst, clear_cmd_struct);
	}
	return (0);
}