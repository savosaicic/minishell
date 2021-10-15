#include "minishell.h"

t_ttype		get_token_type(char *token)
{
	if (!ft_strcmp(token, "|"))
		return (T_PIPE);
	else if (!ft_strcmp(token, "<") || !ft_strcmp(token, ">"))
		return (T_REDIRECT);
	else
		return (T_WORD);
}

t_token	*write_token(char *token)
{
	t_token	*token_struct;

	token_struct = malloc(sizeof(*token_struct));
	if (!token_struct)
		return (NULL);
	token_struct->token = ft_strdup(token);
	if (!token_struct->token)
		return (NULL);
	token_struct->token_type = get_token_type(token);
	return (token_struct);
}

void	print_token(t_list *list)
{
	char **types = ft_split("UNIDENTIFIED WORD REDIRECT PIPE", ' ');

	printf("\n");
	while (list)
	{
		printf("[%s:%s]  ", types[((t_token*)list->content)->token_type], ((t_token*)list->content)->token);
		list = list->next;
	}
	printf("\n");
	printf("__________________________\n\n");
	free_tab(types);
}

t_list	*get_token(t_prg *prg, char *cmd_buffer)
{
	t_list	*token_lst;
	int		i;
	char	buffer[4096];
	char	*expander_var;

	while (*cmd_buffer == ' ')
		cmd_buffer++;

	token_lst = NULL;
	i = 0;
	ft_bzero(buffer, 4096);
	while (*cmd_buffer)
	{
		/* QUOTES */
		if (*cmd_buffer == '\"' || *cmd_buffer == '\'')
		{
			buffer[i] = '\0';
			if (ft_strlen(buffer))
			{
				handle_quote(&cmd_buffer, buffer, &token_lst);
			}
			else
				handle_quote(&cmd_buffer, NULL, &token_lst);
			ft_bzero(buffer, i);
			i = 0;

		}

		/* OPERATOR (|, <, >) */
		else if (*cmd_buffer == '<' || *cmd_buffer == '>' || *cmd_buffer == '|')
		{
			buffer[i] = '\0';
			if (ft_strlen(buffer))
			{
				ft_lstadd_back(&token_lst, ft_lstnew(write_token(buffer)));
			}
			ft_bzero(buffer, i);
			i = 0;
			handle_pipe_and_redirection(&cmd_buffer, &token_lst);
		}

		/* WHITE SPACES */
		else if (*cmd_buffer == ' ')
		{
			while (*cmd_buffer == ' ')
				cmd_buffer++;
			buffer[i] = '\0';
			if (ft_strlen(buffer))
			{
				ft_lstadd_back(&token_lst, ft_lstnew(write_token(buffer)));
			}
			ft_bzero(buffer, i);
			i = 0;
		}

		/* $ */
		else if (*cmd_buffer == '$' && *(cmd_buffer + 1) && *(cmd_buffer + 1) != '$' && *(cmd_buffer + 1) != ' ')
		{
			expander_var = NULL;
			if (ft_strlen(buffer))
				expander_var = ft_strdup(buffer);
			handle_expansion(&cmd_buffer, &expander_var, &token_lst, prg->env_lst);
			ft_bzero(buffer, 4096);
			free(expander_var);
		}

		/* NORMAL CHARS */
		else
		{
			buffer[i] = *cmd_buffer;
			cmd_buffer++;
			i++;
		}
	}
	if (ft_strlen(buffer))
		ft_lstadd_back(&token_lst, ft_lstnew(write_token(buffer)));
	print_token(token_lst);
	return (token_lst);
}