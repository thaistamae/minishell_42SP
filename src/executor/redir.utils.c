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

// Saves the original fds before redirecting
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

// Opens file for writing (output)
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

// Closes fd safely
void	close_fd(int fd)
{
	if (fd > STDERR_FILENO)
		close(fd);
}

// Duplicates and closes
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
