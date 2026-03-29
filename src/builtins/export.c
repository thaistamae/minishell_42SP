/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 13:45:41 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/03/26 23:52:23 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(char *s)
{
	int	i;

	if (!s || !s[0] || ft_isalnum((unsigned char)s[0]))
		return (0);
	i = 0;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum((unsigned char)s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	print_export(t_env *env)
{
	while (env)
	{
		ft_putstr_fd("declare -x", STDOUT_FILENO);
		ft_putstr_fd(env->key, STDOUT_FILENO);
		if (env->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env->value, STDOUT_FILENO);
			ft_putstr_fd("=\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		env = env->next;
	}
	return (0);
}

static int	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (1);
}

static int	handle_single_arg(char *arg, t_env **env)
{
	char	*eq;
	char	*key;
	char	*value;
	int		status;

	if (!is_valid_identifier(arg))
		return (export_error(arg));
	eq = ft_strchr(arg, '=');
	if (!eq)
		return (set_env_var(env, arg, NULL));
	key = ft_substr(arg, 0, eq - arg);
	value = ft_strdup(eq + 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		return (1);
	}
	status = set_env_var(env, key, value);
	free(key);
	free(value);
	return (status);
}

int	builtin_export(t_command *cmd, t_env *env)
{
	int	i;
	int	ret;

	if (!cmd || !cmd->args)
		return (1);
	if (!cmd->args[1])
		return (print_export(env));
	i = 1;
	ret = 0;
	while (cmd->args[i])
	{
		if (handle_single_arg(cmd->args[i], &env) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}
