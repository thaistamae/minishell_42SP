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

static void	handle_exec_error(char *path, char **envp)
{
	if (errno == ENOEXEC)
	{
		execve("/bin/sh", (char *[]){"/bin/sh", path, NULL}, envp);
		perror("minishell");
		exit(126);
	}
	if (errno == EACCES)
	{
		perror("minishell");
		exit(126);
	}
	if (errno == ENOENT)
	{
		perror("minishell");
		exit(127);
	}
	perror("minishell: execve");
	exit(1);
}

static void	exec_child_process(t_command *cmd, t_env *env,
			char *path, char **args)
{
	char	**envp;

	setup_signals_child();
	if (apply_redirections(cmd) == -1)
		exit(1);
	envp = env_to_array(env);
	execve(path, args, envp);
	handle_exec_error(path, envp);
	free_array(envp);
	exit(1);
}

//Função principal que mantém todo o fork e wait
int	execute_external(t_command *cmd, t_env *env)
{
	pid_t	pid;
	int		status;
	char	*path;
	char	**args_valid;
	int		check;

	check = external_setup_args(cmd, &args_valid);
	if (check != -1)
		return (check);
	check = external_prepare_path(&path, args_valid, env);
	if (check != 0)
		return (check);
	pid = fork();
	if (pid < 0)
		return (error_fork());
	if (pid == 0)
		exec_child_process(cmd, env, path, args_valid);
	free(path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

//Executa os comandos internos
int	execute_builtin(t_command *cmd, t_env **env)
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

int	execute_command(t_command *cmd, t_env **env)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (cmd->next)
		return (execute_pipeline(cmd, env));
	if (is_builtin(cmd->args[0]))
		return (execute_builtin(cmd, env));
	return (execute_external(cmd, *env));
}
