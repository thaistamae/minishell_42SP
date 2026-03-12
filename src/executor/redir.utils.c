/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 20:17:05 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/03/11 21:47:43 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Guardar os fds originais antes de redirecionar
int save_std_fds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(0);
	if (*saved_stdin == -1)
		return (-1);
	*saved_stdout = dup(1);
	if (*saved_stdout == -1)
		return (-1);
	return (0);
}

// Voltar stdout/stdin aos valores originais
void restore_std_fds(int saved_stdin, int saved_stdout)
{
	saved_stdin = dup2(0);
	close()
	saved_stdout = dup2(1);
	close()
}

// Abrir arquivo para escrita (output)
int open_output_file(t_redir *redir)
{
	int fd;
	int flags;

	if (redir->type == T_REDIRECT_OUT)
		flags = O_CREAT | O_WRONLY | O_TRUNC;
	else if (redir->type == T_APPEND)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	fd = open(redir->file,flags ,0644);
	return (fd);
}
