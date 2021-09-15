#include "minishell.h"

void init_shell(t_prg *prg, char **env)
{
	char *pwd;

	pwd = search_in_tab(env, "PWD=");
	prg->pwd = ft_strdup(pwd + ft_strlen("PWD="));
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	char	*cmd_buffer;
	t_tokenlst	*head;
	t_prg		prg;

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

			head = get_token(cmd_buffer);

			// cmdlst is a generic linked list, void *content is pointing on a t_cmd struct
			// parse the tokens into a structure for each command
			t_list *cmdlst = parse_tokens(head);

			exec_cmd((t_cmd *)cmdlst->content);

			// Clean the cmdlst
			ft_lstclear(&cmdlst, clear_cmd_struct);
		}

		delete_list(&head);
		free(cmd_buffer);
	}

	return (0);
}
