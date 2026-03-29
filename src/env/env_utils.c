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

// anda na lista nó por nó
t_env	*get_env_node(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

//Procura o nó
//char	*get_env_value(t_env *env, const char *key)
//{
//	t_env	*node;
//
//	node = get_env_node(env, key);
//	if (!node)
//		return (NULL);
//	return (node->value);
//}

//Helper estatico, cria nó na lista e faz malloc/erro
static int	init_new_env_node(t_env **new, const char *key, const char *value)
{
	*new = malloc(sizeof(t_env));
	if (!*new)
		return (1);
	(*new)->key = ft_strdup(key);
	if (!(*new)->key)
	{
		free(*new);
		return (1);
	}
	if (value)
	{
		(*new)->value = ft_strdup(value);
		if (!(*new)->value)
		{
			free((*new)->key);
			free(*new);
			return (1);
		}
	}
	else
		(*new)->value = NULL;
	return (0);
}

//função principal cria/atualiza variáveis
int	set_env_var(t_env **env, const char *key, const char *value)
{
	t_env	*node;
	t_env	*new;
	char	*new_value;

	if (!env || !key)
		return (1);
	node = get_env_node(*env, key);
	if (node)
	{
		free(node->value);
		if (value)
			new_value = ft_strdup(value);
		else
			new_value = NULL;
		if (value && !new_value)
			return (1);
		node->value = new_value;
		return (0);
	}
	if (init_new_env_node(&new, key, value) != 0)
		return (1);
	new->next = *env;
	*env = new;
	return (0);
}

//remove uma variavel de ambiente da lista encadeada
int	unset_env_var(t_env **env, const char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!env || !*env || !key)
		return (1);
	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}
