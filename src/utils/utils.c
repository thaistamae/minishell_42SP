/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:59:29 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/03/09 20:04:55 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	is_builtin(char *cmd)
{
	if (!cmd || cmd[0] == '\0')
		return (0);
	if (ft_strncmp(cmd, "cd" ) == 0)
		return (1);
	if (ft_strncmp(cmd, "echo") == 0)
		return (1);
	if (ft_strncmp(cmd, "env") == 0)
		return (1);
	if (ft_strncmp(cmd, "exit") == 0)
		return (1);
	if (ft_strncmp(cmd, "export") == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strncmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

int execute_builtin(t_command *cmd, t_env *env)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (builtin_cd(cmd, env));
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (builtin_echo(cmd));
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (builtin_env(env));
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (builtin_exit(cmd));
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (builtin_export(cmd, env));
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (builtin_unset(cmd, env));
	return (0);
}

