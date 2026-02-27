#include "minishell.h"

void handle_pipe(t_token **list, int *i)
{
	t_token	*new;

	new = new_token(ft_strdup("|"), T_PIPE);
	if (!new)
		return;
	add_token_back(list, new);
	(*i)++;
}

void handle_word(char *line, t_token **list, int *i)
{
	int		start;
	int 	len;
	char	*word;
	t_token	*new;

	start = *i;
	len = 0;
	while (line[*i] &&
		line[*i] != ' ' &&
		line[*i] != '\t' && 
		line[*i] != '|' && 
		line[*i] != '<' && 
		line[*i] != '>'
	)
	{
		(*i)++;
	}
	len = *i - start;
	word = ft_substr(line, start, len);
	if (!word)
		return;
	new = new_token(word, T_WORD);
	if (!new)
	{
		free(word);
		return;
	}
	add_token_back(list, new);
}

void handle_redirection(t_token **list, char *line, int *i)
{
	t_token	*new;

	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		new = new_token(ft_strdup(">>"), T_APPEND)
		(*i) += 2;
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		new = new_token(ft_strdup("<<"), T_HEREDOC)
		(*i) += 2;
	}
	else if (line[*i] == '>')
	{
		new = new_token(ft_strdup(">"), T_REDIR_OUT);
		(*i)++;
	}
	else (line[*] == '<')
	{
		new = new_token(ft_strdup("<"), T_REDIR_IN);
		(*i)++;
	}
	if (!new)
		return ;
	add_token_back(list, new);
}

t_token *lexer(char *line)
{
	t_token	*list;
	int		i;

	list = NULL;
	i = 0;

	while (line[i])
	{
		if (is_space(line[i]))
			i++;
		else if (line[i] == '|')
			handle_pipe(&list, &i);
		else if (line[i] == '>' || line[i] == '<')
			handle_redirection(&list, line, &i);
		else if (line[i] == '\'' || line[i] == '"')
			handle_quotes(...)
		else
			handle_word(line, &list, &i);
	}
	return (list);
}