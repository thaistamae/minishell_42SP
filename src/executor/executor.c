/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 22:09:10 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/03/05 18:24:37 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

//Valida se command existe
int	execute_command(t_command *cmd, t_env *env)
{
	//Validação
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	//Decide: Builtin ou Externo?
	if (is_builtin(cmd->args[0]))
		return  execute_builtin(cmd, env);
	return execute_external(cmd, env);
}

//Função para comandos externos ex.: ls, mv, rm, mkdir...
int	execute_external(t_command *cmd, t_env *env)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**envp;
	
	//Verificação de cmd
	if (!cmd || !cmd->args || !cmd->args[0]) 
		return (1);

	//Encontrar executavel
	path = find_executable(cmd->args[0], env);
	if (!path)
		return (error_command_not_found(cmd->args[0]));
	//Cria processo filho
	pid = fork();
	if (pid < 0)
		return (error_fork());
	//No processo filho (pid == 0)
	if (pid == 0)
	{
		envp = env_to_array(env);
		execve(path, cmd->args, envp);
		free_array(envp);
		exit(1); //Se execve falhar
	}
	free(path);
	waitpid(pid, &status, 0);

	//Processar código de saída
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

