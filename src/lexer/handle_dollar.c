/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <ttamae@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 12:03:39 by ttamae            #+#    #+#             */
/*   Updated: 2026/03/29 12:03:39 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Adds an entire string to the builder buffer
static void	append_str(t_builder *b, char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		append_char(&b->buffer, &b->len, &b->cap, str[j]);
		j++;
	}
}

// Handles the expansion of the special variable $?
// Adds the current shell exit_status to the buffer
static int	handle_exit_status(char *line, int *i, t_builder *b, t_shell *shell)
{
	char	*status;

	if (line[*i] != '?')
		return (0);
	status = ft_itoa(shell->exit_status);
	if (!status)
		return (1);
	append_str(b, status);
	free(status);
	(*i)++;
	return (1);
}

// Reads the name of an environment variable after '$'
// Searches for its value in envp and adds to the buffer
static void	handle_env_var(char *line, int *i, t_builder *b, t_shell *shell)
{
	int		start;
	char	*var;
	char	*value;

	start = *i;
	while (ft_isalnum(line[*i]) || line[*i] == '_')
		(*i)++;
	var = ft_substr(line, start, *i - start);
	if (!var)
		return ;
	value = get_env_value(shell->env, var);
	if (value)
		append_str(b, value);
	free(var);
}

// Handles the expansion of variables started by '$'
// Can expand $?, environment variables or treat '$' literally
void	handle_dollar(char *line, int *i, t_builder *b, t_shell *shell)
{
	(*i)++;
	if (handle_exit_status(line, i, b, shell))
		return ;
	if (!ft_isalpha(line[*i]) && line[*i] != '_')
	{
		append_char(&b->buffer, &b->len, &b->cap, '$');
		return ;
	}
	handle_env_var(line, i, b, shell);
}
