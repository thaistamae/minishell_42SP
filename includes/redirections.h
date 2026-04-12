/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 01:30:46 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/03/14 01:47:27 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H
# include "structs.h"

int		apply_redirections(t_command *cmd);
int		handle_input_redirect(t_redir *redir);
int		handle_output_redirect(t_redir *redir);
int		handle_heredoc_redirect(t_redir *redir);

int		save_std_fds(int *saved_stdin, int *saved_stdout);
void	restore_std_fds(int saved_stdin, int saved_stdout);
int		dup2_and_close(int fd, int target);
void	close_fd(int fd);
int		open_output_file(t_redir *redir);
int		open_input_file(t_redir *redir);

#endif