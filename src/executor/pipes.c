/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 21:31:42 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/03/18 21:31:42 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child_command(t_command *cmd, t_env *env)
{
	char	*path;
	char	**envp;

	if (!cmd)
		_exit(1);
	if (apply_redirections(cmd) == -1)
		_exit(1);
	if (!cmd->args || !cmd->args[0])
		_exit(1);
	if (is_builtin(cmd->args[0]))
		_exit(execute_builtin(cmd, &env));
	path = find_executable(cmd->args[0], env);
	if (!path)
	{
		error_command_not_found(cmd->args[0]);
		_exit(127);
	}
	envp = env_to_array(env);
	execve(path, cmd->args, envp);
	free_array(envp);
	free(path);
	error_command_not_found(cmd->args[0]);
	_exit(126);
}

//Cria o pipe somente se houver próximo comando
static int	create_pipe_if_needed(t_command *curent, int pipefd[2])
{
	if (!curent->next)
	{
		pipefd[0] = -1;
		pipefd[1] = -1;
		return (0);
	}
	if (pipe(pipefd) == -1)
		return (error_fork());
	return (0);
}

static int	fork_and_setup(t_command *cur, t_env **env,
				int prev_fd, int pipefd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (error_fork());
	if (pid == 0)
	{
		if (prev_fd != -1)
		{
			dup2(prev_fd, STDIN_FILENO);
			safe_close(prev_fd);
		}
		if (cur->next)
		{
			dup2(pipefd[1], STDOUT_FILENO);
			safe_close(pipefd[1]);
		}
		safe_close(pipefd[0]);
		exec_child_command(cur, *env);
	}
	return (pid);
}

static int	execute_pipeline_loop(t_command *cmd, t_env **env,
				pid_t *pids, int count)
{
	int			i;
	int			prev_fd;
	int			pipefd[2];
	t_command	*cur;

	i = 0;
	prev_fd = -1;
	cur = cmd;
	while (cur)
	{
		if (create_pipe_if_needed(cur, pipefd) == -1)
			return (1);
		pids[i] = fork_and_setup(cur, env, prev_fd, pipefd);
		if (pids[i] < 0)
			return (1);
		if (prev_fd != -1)
			safe_close(prev_fd);
		safe_close(pipefd[1]);
		prev_fd = pipefd[0];
		i++;
		cur = cur->next;
	}
	(void)count;
	return (0);
}

int	execute_pipeline(t_command *cmd, t_env **env)
{
	int		count;
	pid_t	*pids;
	int		status;

	if (!cmd)
		return (1);
	count = count_commands(cmd);
	pids = alloc_pids(count);
	if (!pids)
		return (1);
	if (execute_pipeline_loop(cmd, env, pids, count) == -1)
	{
		free(pids);
		return (1);
	}
	status = wait_children(pids, count);
	free(pids);
	return (status);
}
