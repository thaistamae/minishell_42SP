/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <ttamae@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 11:59:08 by ttamae            #+#    #+#             */
/*   Updated: 2026/03/29 11:59:08 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "structs.h"

int			validate_syntax(t_token *tokens);
t_command	*parse_commands(t_token *tokens);
t_command	*new_command(void);
int			add_arg(t_command *cmd, char *value);
t_redir		*new_redir(t_token_type type, char *file);
void		add_redir(t_command *cmd, t_redir *redir);
void		parser_handle_redirection(t_command *cmd, t_token **tok);
int			is_redirection(t_token_type type);

//testes
void		print_commands(t_command *cmd);
void		print_redirs(t_redir *r);

#endif
