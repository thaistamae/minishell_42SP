/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 21:34:20 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/04/12 11:18:40 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Counts how many commands exist in the linked list
int	count_commands(t_command *cmd)
{
	int	n;

	n = 0;
	while (cmd)
	{
		n++;
		cmd = cmd->next;
	}
	return (n);
}

// Dynamically allocates a pid_t array with size n
pid_t	*alloc_pids(int n)
{
	pid_t	*p;

	p = malloc(sizeof(pid_t) * n);
	return (p);
}

// Closes the fds only if valid
void	safe_close(int fd)
{
	if (fd != -1)
		close(fd);
}

// Waits for processes and returns their status
int	wait_children(pid_t *pids, int n)
{
	int	i;
	int	status;
	int	last;

	i = 0;
	last = 1;
	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			last = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			last = 128 + WTERMSIG(status);
		i++;
	}
	return (last);
}

// After parsing, the pipe manifests as cmd->next != NULL.
// There is no "|" in args — so we just need to check the next pointer.
bool	has_pipe(t_command *cmd)
{
	return (cmd != NULL && cmd->next != NULL);
}
