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

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_prg		prg;
	t_list		*cmd_lst;

	init_shell(&prg, env);
	int debug = 0;
	while (1)
	{
		cmd_lst = get_command_lst(&prg);
		while (cmd_lst)
		{
			((t_cmd *)cmd_lst->content)->path = write_command(&prg, ((t_cmd *)cmd_lst->content)->args);
			if (is_builtin(((t_cmd *)(cmd_lst->content))->args[0]))
				execute_builtin(&prg, (t_cmd *)cmd_lst->content);
			else
				execute_command(&prg, (t_cmd *)cmd_lst->content);
			cmd_lst = cmd_lst->next;
		}
		ft_lstclear(&cmd_lst, clear_cmd_struct);
		debug++;
	}
	return (0);
}
