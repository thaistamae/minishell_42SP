/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 16:54:20 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/04/04 17:18:56 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtin(t_command *cmd, t_env **env)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo(cmd));
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (builtin_cd(cmd, *env));
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (builtin_env(*env));
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (builtin_export(cmd, env));
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (builtin_unset(cmd, env));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (builtin_exit(cmd));
	return (1);
}

void	restore_std_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
