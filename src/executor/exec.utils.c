/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 16:04:42 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/03/14 00:59:07 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Duplica strings e cria um array a partir do ambiente
static char	*resolve_slash_command(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

// Procura o comando em cada diretório do PATH e retorna o caminho completo
static char	*find_in_path_dirs(char **dirs, char *cmd)
{
	int		i;
	char	*temp;
	char	*full_path;

	i = 0;
	while (dirs[i])
	{
		temp = ft_strjoin(dirs[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

// 
char	*find_executable(char *cmd, t_env *env)
{
	char	**dirs;
	char	*path_value;
	char	*path_cmd;

	if (ft_strchr(cmd, '/') != NULL)
		return (resolve_slash_command(cmd));
	path_value = get_env_value(env, "PATH");
	if (!path_value)
		return (NULL);
	dirs = ft_split(path_value, ':');
	if (!dirs)
		return (NULL);
	path_cmd = find_in_path_dirs(dirs, cmd);
	free_array(dirs);
	return (path_cmd);
}

// Verifica se o comando é um built-in
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	is_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	return (S_ISDIR(st.st_mode));
}
