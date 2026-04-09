/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 21:34:20 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/04/04 13:00:16 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Conta quantos comandos existem na lista ligada
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

//Aloca dinamicamente um array de pid_t com tamanho n
pid_t	*alloc_pids(int n)
{
	pid_t	*p;

	p = malloc(sizeof(pid_t) * n);
	return (p);
}

//Fecha os fds apenas se for válido
void	safe_close(int fd)
{
	if (fd != -1)
		close(fd);
}

//Espera os processos e retorna os status
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

// Após o parser, o pipe se manifesta como cmd->next != NULL.
// Não existe "|" nos args — por isso basta checar o ponteiro next.
bool	has_pipe(t_command *cmd)
{
	return (cmd != NULL && cmd->next != NULL);
}
