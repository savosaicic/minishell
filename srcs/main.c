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
			t_list *cmdlst = parse_tokens(head);


			int i = 0;
			while (cmdlst)
			{
				printf("----------------------------------\n");
				printf("cmd number %d\nname : %s\n\n", i, ((t_cmd*)cmdlst->content)->args[0]);
				fflush(stdout);
				exec_cmd((t_cmd *)cmdlst->content);
				cmdlst = cmdlst->next;
				i++;
			}

		}

	//	print_list(head);
		delete_list(&head);
		free(cmd_buffer);
	}

	return (0);
}
