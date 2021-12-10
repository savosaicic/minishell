#include "minishell.h"


int ft_onlychr(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i++] != c)
			return (0);
	}
	return (1);
}

t_ttype	get_token_type(char *token)
{
	if (ft_onlychr(token, '|'))
		return (T_PIPE);
	else if (!ft_strcmp(token, ">>"))
		return (T_DGREAT);
	else if (!ft_strcmp(token, "<<"))
		return (T_DLESS);
	else if (ft_onlychr(token, '<') || ft_onlychr(token, '>'))
		return (T_REDIRECT);
	else if (!ft_strcmp(token, "<") || !ft_strcmp(token, ">"))
		return (T_REDIRECT);
	else if (ft_strchr(token, '='))
		return (T_ASSIGN);
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

static void	set_to_zero(int *i, t_list **token_lst)
{
	*token_lst = NULL;
	*i = 0;
}

t_list	*get_token(char *cmd_buffer)
{
	t_list	*token_lst;
	int		i;
	char	*buffer;

	skip_spaces(&cmd_buffer);
	set_to_zero(&i, &token_lst);
	buffer = xxmalloc(sizeof(char) * 4096);
	ft_bzero(buffer, 4096);
	while (*cmd_buffer)
	{
		if (*cmd_buffer == '\"' || *cmd_buffer == '\'')
			i = lex_quotes(&token_lst, &cmd_buffer, &buffer);
		else if (*cmd_buffer == '<' || *cmd_buffer == '>' || *cmd_buffer == '|')
			i = lex_operators(&token_lst, &cmd_buffer, &buffer);
		else if (*cmd_buffer == ' ')
			i = lex_spaces(&token_lst, &cmd_buffer, &buffer);
		else if (*cmd_buffer == '$' && *(cmd_buffer + 1) && *(cmd_buffer + 1)
			!= '$' && *(cmd_buffer + 1) != ' ')
			i = lex_expansion(&token_lst, &cmd_buffer, &buffer);
		else
			i = lex_chars(i, &cmd_buffer, &buffer);
	}
	if (ft_strlen(buffer))
		ft_lstadd_back(&token_lst, ft_lstnew(write_token(buffer)));
	free(buffer);
	return (token_lst);
}
