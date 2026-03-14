/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 20:07:53 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/03/14 00:47:18 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "redirections.h"

//Abre arquivo para <
int	open_input_file(t_redir *redir)
{
	int	fd;

	if (!redir || !redir->file)
		return (-1);
	fd = open(redir->file, O_RDONLY, 0);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(redir->file, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	return (fd);
}

//Lida com redirecionamento de entrada <
int	handle_input_redirect(t_redir *redir)
{
	int	fd;

	fd = open_input_file(redir);
	if (fd == -1)
		return (-1);
	if (dup2_and_close(fd, STDIN_FILENO) == -1)
		return (-1);
	return (0);
}

//Lida com redirecionamento de saida >
int	handle_output_redirect(t_redir *redir)
{
	int	fd;

	fd = open_output_file(redir);
	if (fd == -1)
		return (-1);
	if (dup2_and_close(fd, STDOUT_FILENO) == -1)
		return (-1);
	return (0);
}

//lida com heredoc << 
int	handle_heredoc_redirect(t_redir *redir)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
		return (-1);
	while (1)
	{
		line = readline(">");
		if (!line)
			break ;
		if (ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	if (dup2_and_close(pipe_fd[0], STDIN_FILENO) == -1)
		return (-1);
	return (0);
}

//Aplica os redirecionamentos de acordo com o comando
int	apply_redirections(t_command *cmd)
{
	t_redir	*current;

	if (!cmd || !cmd->redirs)
		return (0);
	current = cmd->redirs;
	while (current != NULL)
	{
		if (current->type == T_REDIRECT_IN)
		{
			if (handle_input_redirect(current) == -1)
				return (-1);
		}
		else if (current->type == T_REDIRECT_OUT || current->type == T_APPEND)
		{
			if (handle_output_redirect(current) == -1)
				return (-1);
		}
		else if (current->type == T_HEREDOC)
		{
			if (handle_heredoc_redirect(current) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
