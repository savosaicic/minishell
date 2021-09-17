#include "minishell.h"

void init_shell(t_prg *prg, char **env)
{
	char *pwd;

	pwd = search_in_tab(env, "PWD=");
	prg->pwd = ft_strdup(pwd + ft_strlen("PWD="));
	prg->env = env;
	prg->cmd_buffer = NULL;
}

char	*init_command(t_prg *prg, char **cmd)
{
	char **paths;
	char *path;

	paths = ft_split(search_in_tab(prg->env, "PATH=") + ft_strlen("PATH="), ':');
	path = get_cmd_path(paths, cmd[0], prg->pwd);
	free_tab(paths);
	return (path);
}

t_list 	*get_command(t_prg *prg)
{
	t_list		*token_lst;
	t_list		*cmdlst;

	prg->cmd_buffer = readline("$> ");
	if (!prg->cmd_buffer)
		exit_success(prg, 0);
	add_history(prg->cmd_buffer);
	token_lst = get_token(prg->cmd_buffer);
	cmdlst = parse_tokens(token_lst);
	ft_lstclear(&token_lst, clear_token_struct);
	free(prg->cmd_buffer);
	return (cmdlst);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_prg		prg;
	t_list		*cmdlst;

	init_shell(&prg, env);
	while (1)
	{
		cmdlst = get_command(&prg);
		((t_cmd*)cmdlst->content)->path = init_command(&prg, ((t_cmd*)cmdlst->content)->args);
		execute_command(&prg, (t_cmd *)cmdlst->content);
		ft_lstclear(&cmdlst, clear_cmd_struct);
	}
	return (0);
}
