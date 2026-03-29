/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <ttamae@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 11:57:46 by ttamae            #+#    #+#             */
/*   Updated: 2026/03/29 11:57:46 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "structs.h"

t_token	*new_token(char *value, t_token_type type);
void	add_token_back(t_token **list, t_token *new);
void	free_tokens(t_token *list);

void	append_char(char **buffer, int *len, int *cap, char c);

t_token	*lexer(char *line, t_shell *shell);
void	handle_word(char *line, int *i, t_token **list, t_shell *shell);
void	handle_dollar(char *line, int *i, t_builder *b, t_shell *shell);
void	print_tokens(t_token *list);

#endif
