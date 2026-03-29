/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 13:39:48 by ttamae            #+#    #+#             */
/*   Updated: 2026/03/22 13:39:52 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "structs.h"

int		has_unclosed_quotes(char *line);
int		has_invalid_chars(char *line);
t_token	*new_token(char *value, t_token_type type);
void	add_token_back(t_token **list, t_token *new);
void	free_tokens(t_token *list);

void	append_char(char **buffer, int *len, int *cap, char c);

t_token	*lexer(char *line, t_shell *shell);
int		handle_word(char *line, int *i, t_token **list, t_shell *shell);
void	handle_dollar(char *line, int *i, t_builder *b, t_shell *shell);

//teste
void	print_tokens(t_token *list);

#endif
