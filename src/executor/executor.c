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

static void	exec_child_process(t_command *cmd, t_env *env, char *path)
{
	char	**envp;

	setup_signals_child();
	if (apply_redirections(cmd) == -1)
		exit(1);
	envp = env_to_array(env);
	execve(path, cmd->args, envp);
	perror("minishell: execve");
	free_array(envp);
	if (errno == ENOENT)
		exit(127);
	else if (errno == EACCES || errno == ENOEXEC || errno == EISDIR)
		exit(126);
	else
		exit(1);
}

//Função para comandos externos ex.: ls, mv, rm, mkdir...
int	execute_external(t_command *cmd, t_env *env)
{
	pid_t	pid;
	int		status;
	char	*path;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	path = find_executable(cmd->args[0], env);
	if (!path)
		return (error_command_not_found(cmd->args[0]));
	pid = fork();
	if (pid < 0)
		return (error_fork());
	if (pid == 0)
		exec_child_process(cmd, env, path);
	free(path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

//Execução de funções built-in
int	execute_builtin(t_command *cmd, t_env *env)
{
	int	saved_stdin;
	int	saved_stdout;
	int	ret;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (cmd->next && ft_strcmp(cmd->args[0], "cd") == 0)
		return (0);
	if (save_std_fds(&saved_stdin, &saved_stdout) == -1)
		return (1);
	if (!cmd->next && apply_redirections(cmd) == -1)
	{
		restore_std_fds(saved_stdin, saved_stdout);
		return (1);
	}
	ret = run_builtin(cmd, env);
	restore_std_fds(saved_stdin, saved_stdout);
	return (ret);
}

//Valida se command existe
int	execute_command(t_command *cmd, t_env *env)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (cmd->next && has_pipe(cmd))
		return (execute_pipeline(cmd, env));
	if (is_builtin(cmd->args[0]))
		return (execute_builtin(cmd, env));
	return (execute_external(cmd, env));
}
