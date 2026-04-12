/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <ttamae@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 12:02:11 by ttamae            #+#    #+#             */
/*   Updated: 2026/03/29 12:02:11 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns error if next token after pipe is empty or pipe
static int	check_pipe_error(t_token *token)
{
	if (!token->next)
		return (0);
	if (token->next->type == T_PIPE)
		return (0);
	return (1);
}

// Returns error if next token after pipe is empty or not a word
static int	check_redirection_error(t_token *token)
{
	if (!token->next)
		return (0);
	if (token->next->type != T_WORD)
		return (0);
	return (1);
}

// Checks if token is a redirection type
int	is_redirection(t_token_type type)
{
	if (type == T_REDIRECT_IN
		|| type == T_REDIRECT_OUT
		|| type == T_APPEND
		|| type == T_HEREDOC)
		return (1);
	return (0);
}

// Validates the token list
// If there are no tokens validation is ok
// First token cannot be pipe
// Traverses the token list and performs pipe and redirection validations
int	validate_syntax(t_token *tokens)
{
	t_token	*tmp;

	if (!tokens)
		return (1);
	if (tokens->type == T_PIPE)
		return (0);
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == T_PIPE && !check_pipe_error(tmp))
			return (0);
		if (is_redirection(tmp->type)
			&& !check_redirection_error(tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int	only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}
