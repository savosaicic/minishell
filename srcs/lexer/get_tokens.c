#include "minishell.h"

t_ttype	get_token_type(char *token)
{
	if (!ft_strcmp(token, "|"))
		return (T_PIPE);
	else if (!ft_strcmp(token, "<") || !ft_strcmp(token, ">"))
		return (T_REDIRECT);
	else if (ft_strchr(token, '='))
		return (T_ASSIGN);
	else if (!ft_strcmp(token, ">>"))
		return (T_DGREAT);
	else if (!ft_strcmp(token, "<<"))
		return (T_DLESS);
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
	char **types = ft_split("UNIDENTIFIED WORD REDIRECT DGREAT DLESS PIPE ASSIGN", ' ');

	printf("\n");
	while (list)
	{
		printf("[%s:%s]  ", types[((t_token *)list->content)->token_type], ((t_token *)list->content)->token);
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
	char	*buffer;

	skip_spaces(&cmd_buffer);
	token_lst = NULL;
	i = 0;
	buffer = xmalloc(sizeof(char) * 4096);
	ft_bzero(buffer, 4096);
	while (*cmd_buffer)
	{
		if (*cmd_buffer == '\"' || *cmd_buffer == '\'')
			i = lex_quotes(prg, &token_lst, &cmd_buffer, &buffer);
		else if (*cmd_buffer == '<' || *cmd_buffer == '>' || *cmd_buffer == '|')
			i = lex_operators(prg, &token_lst, &cmd_buffer, &buffer);
		else if (*cmd_buffer == ' ')
			i = lex_spaces(prg, &token_lst, &cmd_buffer, &buffer);
		else if (*cmd_buffer == '$' && *(cmd_buffer + 1) && *(cmd_buffer + 1) != '$' && *(cmd_buffer + 1) != ' ')
			i = lex_expansion(prg, &token_lst, &cmd_buffer, &buffer);
		else
			i = lex_chars(i, &cmd_buffer, &buffer);
	}
	if (ft_strlen(buffer))
		ft_lstadd_back(&token_lst, ft_lstnew(write_token(buffer)));
	return (token_lst);
}
