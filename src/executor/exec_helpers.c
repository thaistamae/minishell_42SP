/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 16:04:42 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/03/14 00:59:07 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	resolve_command_path(char **path, char **args)
{
	if (!*path)
	{
		if ((*args)[0] == '/' || ft_strncmp(*args, "./", 2) == 0
			|| ft_strncmp(*args, "../", 3) == 0)
		{
			if (access(*args, F_OK) != 0)
				return (path_not_found(*args));
			*path = ft_strdup(*args);
		}
		else
			return (path_not_found(*args));
	}
	if (is_directory(*path) || access(*path, X_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(*args, STDERR_FILENO);
		if (is_directory(*path))
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		else
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		free(*path);
		return (126);
	}
	return (0);
}

/* Função auxiliar para pular args vazios e definir args_valid */
int	external_setup_args(t_command *cmd, char ***args_valid)
{
	int	i;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	i = 0;
	while (cmd->args[i] && cmd->args[i][0] == '\0')
		i++;
	if (!cmd->args[i])
		return (0);
	*args_valid = &cmd->args[i];
	return (-1);
}

/* Função auxiliar para preparar path e validar comando */
int	external_prepare_path(char **path, char **args_valid, t_env *env)
{
	*path = find_executable(args_valid[0], env);
	return (resolve_command_path(path, args_valid));
}
