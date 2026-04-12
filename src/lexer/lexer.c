/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <ttamae@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 12:04:07 by ttamae            #+#    #+#             */
/*   Updated: 2026/03/29 12:04:07 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Inclui os tokens de | na lista linkada
static void	handle_pipe(t_token **list, int *i)
{
	t_token	*new;

	new = new_token(ft_strdup("|"), T_PIPE);
	if (!new)
		return ;
	add_token_back(list, new);
	(*i)++;
}

//Inclui os tokens de redirection na lista linkada
static void	handle_redirection(t_token **list, char *line, int *i)
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

// Reads the command line and calls other methods
// to create a linked list of tokens according to command types
t_token	*lexer(char *line, t_shell *shell)
{
	t_token	*list;
	int		i;

	i = 0;
	list = NULL;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			i++;
		else if (line[i] == '|')
			handle_pipe(&list, &i);
		else if (line[i] == '>' || line[i] == '<')
			handle_redirection(&list, line, &i);
		else
		{
			if (!handle_word(line, &i, &list, shell))
			{
				free_tokens(list);
				return (NULL);
			}
		}
	}
	return (list);
}
