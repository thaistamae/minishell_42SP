/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 19:09:35 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/03/25 21:43:29 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// monta "KEY=VALUE" (se value for NULL, usa só "KEY=")
static char	*join_key_value(t_env *node)
{
	char	*tmp;
	char	*result;

	if (!node || !node->key)
		return (NULL);
	tmp = ft_strjoin(node->key, "=");
	if (!tmp)
		return (NULL);
	if (node->value)
	{
		result = ft_strjoin(tmp, node->value);
		free(tmp);
		return (result);
	}
	return (tmp);
}

// preenche o array envp a partir da lista encadeada
static int	fill_env_array(t_env *env, char **envp)
{
	int		i;
	char	*entry;

	i = 0;
	while (env)
	{
		entry = join_key_value(env);
		if (!entry)
		{
			while (i > 0)
			{
				free(envp[i - 1]);
				i--;
			}
			return (1);
		}
		envp[i] = entry;
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (0);
}

static	int	env_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

// converte lista t_env* em char ** para execve
char	**env_to_array(t_env *env)
{
	char	**envp;
	int		size;

	if (!env)
		return (NULL);
	size = env_size(env);
	envp = malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	if (fill_env_array(env, envp) != 0)
	{
		free(envp);
		return (NULL);
	}
	return (envp);
}
