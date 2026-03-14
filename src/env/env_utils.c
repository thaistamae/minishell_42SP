/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:59:19 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/03/14 01:32:30 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_array(t_env *env)
{
	t_env	*current;
	char	**envp;
	char	*temp;
	int		count;
	int		i;

	if (!env)
		return (NULL);
	count = 0;
	current = env;
	while (current)
	{
		count++;
		current = current->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	current = env;
	i = 0;
	while (current)
	{
		temp = ft_strjoin(current->key, "=");
		envp[i] = ft_strjoin(temp, current->value);
		free(temp);
		current = current->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
