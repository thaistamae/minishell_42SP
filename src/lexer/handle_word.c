/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <ttamae@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 12:03:54 by ttamae            #+#    #+#             */
/*   Updated: 2026/03/29 12:03:54 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

//Lida com conteúdo entre aspas simples ou duplas
//Adiciona os caracteres ao buffer até encontrar a aspas de fechamento
//Permite expansão de variáveis apenas dentro de aspas duplas
static int	handle_quotes(char *line, int *i, t_builder *b, t_shell *shell)
{
	char	quote;

	quote = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != quote)
	{
		if (quote == '"' && line[*i] == '$')
			handle_dollar(line, i, b, shell);
		else
		{
			append_char(&b->buffer, &b->len, &b->cap, line[*i]);
			(*i)++;
		}
	}
	if (!line[*i])
		return (0);
	(*i)++;
	return (1);
}

//Constrói uma palavra lendo os caracteres da linha de comando
//Adiciona os caracteres ao buffer até encontrar espaço ou operador
//Também trata aspas e expansão de variáveis
static int	build_word(char *line, int *i,
						t_builder *b, t_shell *shell)
{
	while (line[*i] && !ft_isspace(line[*i])
		&& line[*i] != '|'
		&& line[*i] != '<'
		&& line[*i] != '>')
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			if (!handle_quotes(line, i, b, shell))
				return (0);
		}
		else if (line[*i] == '$')
			handle_dollar(line, i, b, shell);
		else
			append_char(&b->buffer, &b->len, &b->cap,
				line[(*i)++]);
	}
	return (1);
}

//Adiciona um caractere ao buffer do builder
//Realoca o buffer caso a capacidade seja atingida
void	append_char(char **buffer, int *len, int *cap, char c)
{
	char	*new_buffer;
	int		i;

	if (*len + 1 >= *cap)
	{
		*cap *= 2;
		new_buffer = malloc(*cap);
		if (!new_buffer)
			return ;
		i = 0;
		while (i < *len)
		{
			new_buffer[i] = (*buffer)[i];
			i++;
		}
		free(*buffer);
		*buffer = new_buffer;
	}
	(*buffer)[*len] = c;
	(*len)++;
}

//Cria um token do tipo WORD a partir do conteúdo construído no buffer
//Chama build_word para ler a palavra e adiciona o token na lista
void	handle_word(char *line, int *i,
					t_token **list, t_shell *shell)
{
	t_builder	b;
	t_token		*new;

	b.len = 0;
	b.cap = 32;
	b.buffer = malloc(b.cap);
	if (!b.buffer)
		return ;
	if (!build_word(line, i, &b, shell))
	{
		free(b.buffer);
		return ;
	}
	b.buffer[b.len] = '\0';
	new = new_token(b.buffer, T_WORD);
	if (!new)
	{
		free(b.buffer);
		return ;
	}
	add_token_back(list, new);
}
