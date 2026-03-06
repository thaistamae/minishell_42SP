#ifndef EXECUTOR_H
# define EXECUTOR_H

#include "minishell.h"
#include <sys/wait.h>
#include <unistd.h>

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
char	*get_env_value(char *key, t_env *env);

int		error_command_not_found(char *args);
int		error_fork(void);
int	free_array(char **array);

#endif