/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 23:11:20 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/04/12 15:17:09 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	split_env_entry(char *entry, char **key, char **value)
{
	char	*c;
	int		key_len;

	c = ft_strchr(entry, '=');
	if (!c)
		return (1);
	key_len = c - entry;
	*key = ft_substr(entry, 0, key_len);
	*value = ft_strdup(c + 1);
	if (!*key || !*value)
	{
		free(*key);
		free(*value);
		return (1);
	}
	return (0);
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	char	*key;
	char	*value;
	int		i;

	env = NULL;
	i = 0;
	while (envp && envp[i])
	{
		if (split_env_entry(envp[i], &key, &value) == 0)
		{
			if (set_env_var(&env, key, value) != 0)
			{
				free(key);
				free(value);
				return (env);
			}
			free(key);
			free(value);
		}
		i++;
	}
	return (env);
}
