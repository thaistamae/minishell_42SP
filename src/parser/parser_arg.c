/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <ttamae@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 13:37:18 by ttamae            #+#    #+#             */
/*   Updated: 2026/03/22 13:37:20 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//conta a quantidade de argumentos
static int	count_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
		i++;
	return (i);
}

//cria uma comando vazio
t_command	*new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

//adiciona um argumento a lista de argumentos
//conta quantos argumentos existem na lista
//cria um novo array no malloc adiciona mais dois para o novo elemento + NULL
int	add_arg(t_command *cmd, char *value)
{
	char	**new;
	int		i;
	int		len;

	len = count_args(cmd->args);
	new = malloc(sizeof(char *) * (len + 2));
	if (!new)
		return (0);
	i = 0;
	while (i < len)
	{
		new[i] = cmd->args[i];
		i++;
	}
	new[i] = ft_strdup(value);
	i++;
	new[i] = NULL;
	free(cmd->args);
	cmd->args = new;
	return (1);
}
