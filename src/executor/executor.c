/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:09:10 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/03/14 02:01:15 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"
#include "redirections.h"

//Função para comandos externos ex.: ls, mv, rm, mkdir...
int	execute_external(t_command *cmd, t_env *env)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**envp;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	path = find_executable(cmd->args[0], env);
	if (!path)
		return (error_command_not_found(cmd->args[0]));
	pid = fork();
	if (pid < 0)
		return (error_fork());
	if (pid == 0)
	{
		envp = env_to_array(env);
		execve(path, cmd->args, envp);
		free_array(envp);
		exit(1);
	}
	free(path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

// TODO: Implementar builtins depois
int	execute_builtin(t_command *cmd, t_env *env)
{
	(void)env;
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->args[0], STDERR_FILENO);
	ft_putstr_fd(": builtin not implemented yet\n", STDERR_FILENO);
	return (1);
}

//Valida se command existe
int	execute_command(t_command *cmd, t_env *env)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (is_builtin(cmd->args[0]))
		return (execute_builtin(cmd, env));
	return (execute_external(cmd, env));
}
