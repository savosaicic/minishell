#include "minishell.h"

void init_shell(t_prg *prg, char **env)
{
	char *pwd;

	pwd = search_in_tab(env, "PWD=");
	prg->pwd = ft_strdup(pwd + ft_strlen("PWD="));
	prg->env = env;
}

char	*init_cmd(t_prg *prg, char **cmd)
{
	char **paths;
	char *path;

	paths = ft_split(search_in_tab(prg->env, "PATH=") + ft_strlen("PATH="), ':');
	path = get_cmd_path(paths, cmd[0], prg->pwd);
	free_tab(paths);
	return (path);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char		*cmd_buffer;
	t_prg		prg;
	t_list		*cmdlst;
	t_list		*token_lst;

	init_shell(&prg, env);
	while (1)
	{
		cmd_buffer = readline("$> ");
		if (!cmd_buffer)
		{
			rl_clear_history();
			exit(0);
		}
		else if (ft_strlen(cmd_buffer))
		{
			add_history(cmd_buffer);
			token_lst = get_token(cmd_buffer);
			cmdlst = parse_tokens(token_lst);
			((t_cmd*)cmdlst->content)->path = init_cmd(&prg, ((t_cmd*)cmdlst->content)->args);
			exec_cmd(&prg, (t_cmd *)cmdlst->content);
			ft_lstclear(&cmdlst, clear_cmd_struct);
		}
		ft_lstclear(&token_lst, clear_token_struct);
		free(cmd_buffer);
	}
	return (0);
}
