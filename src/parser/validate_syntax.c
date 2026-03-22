/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 13:37:41 by ttamae            #+#    #+#             */
/*   Updated: 2026/03/22 13:37:42 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//retorna erro de próximo token depois de pipe for vazio ou pipe
static int	check_pipe_error(t_token *token)
{
	if (!token->next)
		return (0);
	if (token->next->type == T_PIPE)
		return (0);
	return (1);
}

//retorna erro de próximo token depois de pipe for vazio ou não for palavra
static int	check_redirection_error(t_token *token)
{
	if (!token->next)
		return (0);
	if (token->next->type != T_WORD)
		return (0);
	return (1);
}

//verifica se token é do tipo redirection
int	is_redirection(t_token_type type)
{
	if (type == T_REDIRECT_IN
		|| type == T_REDIRECT_OUT
		|| type == T_APPEND
		|| type == T_HEREDOC)
		return (1);
	return (0);
}

//valida a lista de tokens
//se não houver tokens validação ok
//primeiro token não pode ser pipe
//percorre a lista de tokens e faz as validações de pipe e de redirection
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
