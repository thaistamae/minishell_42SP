/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 13:37:31 by ttamae            #+#    #+#             */
/*   Updated: 2026/03/22 13:37:32 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*new_redir(t_token_type type, char *file)
{
	t_redir	*r;

	r = malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	r->type = type;
	r->file = ft_strdup(file);
	r->next = NULL;
	return (r);
}

void	add_redir(t_command *cmd, t_redir *redir)
{
	t_redir	*tmp;

	if (!cmd->redirs)
	{
		cmd->redirs = redir;
		return ;
	}
	tmp = cmd->redirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = redir;
}

void	parser_handle_redirection(t_command *cmd, t_token **tok)
{
	t_redir	*r;

	r = new_redir((*tok)->type, (*tok)->next->value);
	if (!r)
		return ;
	add_redir(cmd, r);
	*tok = (*tok)->next;
}
