/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 13:45:41 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/04/08 22:55:38 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_export(t_env *env)
{
	while (env)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env->key, STDOUT_FILENO);
		if (env->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		env = env->next;
	}
	return (0);
}

static int	handle_no_equal(char *key, t_env **env)
{
	t_env	*cur;

	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
			return (0);
		cur = cur->next;
	}
	return (set_env_var(env, key, NULL));
}

static int	handle_single_arg(char *arg, t_env **env)
{
	char	*eq;
	char	*key;
	char	*value;
	int		status;

	key = get_valid_key(arg, &eq);
	if (!key)
		return (export_error(arg));
	if (!eq)
	{
		status = handle_no_equal(key, env);
		free(key);
		return (status);
	}
	value = ft_strdup(eq + 1);
	if (!value)
	{
		free(key);
		return (1);
	}
	status = set_env_var(env, key, value);
	free(key);
	free(value);
	return (status);
}

int	builtin_export(t_command *cmd, t_env **env)
{
	int	i;
	int	ret;

	if (!cmd || !cmd->args)
		return (1);
	if (!cmd->args[1])
		return (print_export(*env));
	i = 1;
	ret = 0;
	while (cmd->args[i])
	{
		if (handle_single_arg(cmd->args[i], env) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}
