/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <ttamae@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 14:39:22 by ttamae            #+#    #+#             */
/*   Updated: 2026/03/22 14:39:24 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//valida se virgulas foram fechadas
int	has_unclosed_quotes(char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"'))
		{
			if (quote == 0)
				quote = line[i];
			else if (quote == line[i])
				quote = 0;
		}
		i++;
	}
	return (quote != 0);
}

//valida se ha caracteres invalidos
int	has_invalid_chars(char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"'))
		{
			if (quote == 0)
				quote = line[i];
			else if (quote == line[i])
				quote = 0;
		}
		else if ((line[i] == ';' || line[i] == '\\') && quote == 0)
			return (1);
		i++;
	}
	return (0);
}
