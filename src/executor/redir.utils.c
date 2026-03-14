/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 20:17:05 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/03/14 01:57:48 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirections.h"

// Guarda os fds originais antes de redirecionar
int	save_std_fds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(0);
	if (*saved_stdin == -1)
		return (-1);
	*saved_stdout = dup(1);
	if (*saved_stdout == -1)
	{
		close(*saved_stdin);
		*saved_stdin = -1;
		return (-1);
	}
	return (0);
}

// Volta stdout/stdin aos valores originais
void	restore_std_fds(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

// Abri arquivo para escrita (output)
int	open_output_file(t_redir *redir)
{
	int	fd;
	int	flags;

	if (!redir || !redir->file)
		return (-1);
	if (redir->type == T_REDIRECT_OUT)
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else if (redir->type == T_APPEND)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	else
		return (-1);
	fd = open(redir->file, flags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redir->file, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	}
	return (fd);
}

//fecha fd com segurança
void	close_fd(int fd)
{
	if (fd > STDERR_FILENO)
		close(fd);
}

//Duplica e fecha
int	dup2_and_close(int fd, int target)
{
	if (fd < 0)
		return (-1);
	if (dup2(fd, target) == -1)
	{
		close_fd(fd);
		return (-1);
	}
	close_fd(fd);
	return (0);
}
