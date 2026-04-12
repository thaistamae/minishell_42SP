/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <ttamae@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 12:01:56 by ttamae            #+#    #+#             */
/*   Updated: 2026/03/29 12:01:56 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Free redirs
static void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = tmp;
	}
}

// Will traverse the tokens and build the linked list with the commands
// Commands are separated into argument lists and redirect list
t_command	*parser(t_token *tokens)
{
	t_command	*head;
	t_command	*current;

	head = new_command();
	if (!head)
		return (NULL);
	current = head;
	while (tokens)
	{
		if (tokens->type == T_WORD)
			add_arg(current, tokens->value);
		else if (is_redirection(tokens->type))
			parser_handle_redirection(current, &tokens);
		else if (tokens->type == T_PIPE)
		{
			current->next = new_command();
			current = current->next;
			tokens = tokens->next;
			continue ;
		}
		tokens = tokens->next;
	}
	return (head);
}

// Free the commands
void	free_commands(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				free(cmd->args[i]);
				i++;
			}
			free(cmd->args);
		}
		if (cmd->redirs)
		{
			free_redirs(cmd->redirs);
		}
		free(cmd);
		cmd = tmp;
	}
}
