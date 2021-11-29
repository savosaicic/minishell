#include "minishell.h"

static int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '\"' || c == '\'' || c == ' ');
}

static char	*quotes_expansion(t_prg *prg, t_list *env_lst, char **cmd_buffer, char quote)
{
	char	buffer[4096];
	char	*expanded_var;
	int		i;

	ft_bzero(buffer, 4096);
	(*cmd_buffer)++;
	i = 0;
	while (**cmd_buffer && **cmd_buffer != quote)
	{
		if (is_space(**cmd_buffer) || **cmd_buffer == '$')
			break;
		buffer[i++] = **cmd_buffer;
		(*cmd_buffer)++;
	}
	if (buffer[0] == '?')
		return(ft_itoa(prg->last_exit_status));
	expanded_var = ft_getenv(env_lst, buffer);
	if (!expanded_var)
		return (ft_strdup(""));
	return (expanded_var);
}

static void	init_vars(char **cmd_buffer, int *i, char *quote, char *buffer)
{
	*quote = **cmd_buffer;
	(*cmd_buffer)++;
	*i = 0;
	ft_bzero(buffer, 4096);
}

static int	add_back(t_list **token_lst, char *buffer, char *str)
{
	if (str)
		ft_lstadd_back(token_lst, ft_lstnew(write_token(ft_strjoin(str, buffer))));
	else if (ft_strlen(buffer))
		ft_lstadd_back(token_lst, ft_lstnew(write_token(buffer)));
	return (0);
}

int	handle_quote(t_prg *prg, char **cmd_buffer, char *str, t_list **token_lst)
{
	char	quote;
	char	buffer[4096];
	int		i;
	char	*tmp;

	init_vars(cmd_buffer, &i, &quote, &buffer[0]);
	while (**cmd_buffer != quote && **cmd_buffer)
	{
		while (**cmd_buffer == '$' && *(*cmd_buffer + 1) && *(*cmd_buffer + 1) != '$' && *(*cmd_buffer + 1) != ' ' && quote != '\'')
		{
			tmp = quotes_expansion(prg, prg->env_lst, cmd_buffer, quote);
			ft_strcat(buffer, tmp);
			i += ft_strlen(tmp);
			free(tmp);
			if (**cmd_buffer == quote)
				break;
		}
		if (**cmd_buffer == quote)
			break;
		buffer[i++] = *(*cmd_buffer)++;
	}
	(*cmd_buffer)++;
	while (!is_operator(**cmd_buffer) && **cmd_buffer)
		buffer[i++] = *(*cmd_buffer)++;
	return (add_back(token_lst, &buffer[0], str));
}