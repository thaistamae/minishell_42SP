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

static void	exec_child_process(t_command *cmd, t_env *env,
			char *path, char **args)
{
	char	**envp;

	setup_signals_child();
	if (apply_redirections(cmd) == -1)
		exit(1);
	envp = env_to_array(env);
	execve(path, args, envp);
	perror("minishell: execve");
	free_array(envp);
	exit(1);
}

int	execute_external(t_command *cmd, t_env *env)
{
	pid_t	pid;
	int		status;
	char	*path;
	int		i;
	char	**args_valid;
	int		check;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	i = 0;
	while (cmd->args[i] && cmd->args[i][0] == '\0')
		i++;
	if (!cmd->args[i])
		return (0);
	args_valid = &cmd->args[i];
	path = find_executable(args_valid[0], env);
	check = resolve_command_path(&path, args_valid);
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
