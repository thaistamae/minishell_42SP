#include "minishell.h"
#include "libft.h"

//Inclui os tokens de | na lista linkada
static void handle_pipe(t_token **list, int *i)
{
	t_token	*new;

	new = new_token(ft_strdup("|"), T_PIPE);
	if (!new)
		return;
	add_token_back(list, new);
	(*i)++;
}

//Inclui os tokens de redirection na lista linkada
static void handle_redirection(t_token **list, char *line, int *i)
{
	t_token	*new;

	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		new = new_token(ft_strdup(">>"), T_APPEND);
		(*i) += 2;
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		new = new_token(ft_strdup("<<"), T_HEREDOC);
		(*i) += 2;
	}
	else if (line[*i] == '>')
	{
		new = new_token(ft_strdup(">"), T_REDIRECT_OUT);
		(*i)++;
	}
	else if (line[*i] == '<')
	{
		new = new_token(ft_strdup("<"), T_REDIRECT_IN);
		(*i)++;
	}
	if (!new)
		return ;
	add_token_back(list, new);
}

//Lê a linha de comando e chama outros métodos
//para criar uma lista linkada de tokens de acordo com os tipos dos comandos
t_token *lexer(char *line, t_shell *shell)
{
	t_token	*list;
	int		i;

	list = NULL;
	i = 0;

	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (line[i] == '|')
			handle_pipe(&list, &i);
		else if (line[i] == '>' || line[i] == '<')
			handle_redirection(&list, line, &i);
		else
			handle_word(line, &i, &list, shell);
	}
	return (list);
}