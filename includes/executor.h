/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 01:46:06 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/03/14 01:51:27 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "structs.h"

int		execute_command(t_command *cmd, t_env *env);
int		execute_external(t_command *cmd, t_env *env);
int		is_builtin(char *cmd);
int		execute_builtin(t_command *cmd, t_env *env);

int		builtin_echo(t_command *cmd);
int		builtin_cd(t_command *cmd, t_env *env);
int		builtin_pwd(void);
int		builtin_export(t_command *cmd, t_env *env);
int		builtin_unset(t_command *cmd, t_env *env);
int		builtin_env(t_env *env);
int		builtin_exit(t_command *cmd);

char	*find_executable(char *cmd, t_env *env);
char	**env_to_array(t_env *env);

int		error_command_not_found(char *cmd);
int		error_fork(void);
void	free_array(char **array);

int		execute_pipeline(t_command *cmd, t_env *env);

//pipes utilities (usados por pipes.c)
int		count_commands(t_command *cmd);
pid_t	*alloc_pids(int n);
void	safe_close(int fd);
int		wait_children(pid_t *pids, int n);
void	setup_child_fds(int prev_fd, int pipe_write);
bool	has_pipe(t_command *cmd);

// Funções de builtin utils
int		run_builtin(t_command *cmd, t_env *env);
int		save_std_fds(int *saved_stdin, int *saved_stdout);
void	restore_std_fds(int saved_stdin, int saved_stdout);
#endif