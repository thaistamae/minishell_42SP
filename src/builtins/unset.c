/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 23:07:54 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/04/04 12:08:11 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_unset_identifier(char *s)
{
	int	i;

	if (!s || !s[0] || ft_isdigit((unsigned char)s[0]))
		return (0);
	i = 0;
	while (s[i])
	{
		if (!ft_isalnum((unsigned char)s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	unset_error(char *arg)
{
	ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (1);
}

int	builtin_unset(t_command *cmd, t_env *env)
{
	int	i;
	int	ret;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	i = 1;
	ret = 0;
	while (cmd->args[i])
	{
		if (!is_valid_unset_identifier(cmd->args[i]))
			ret = unset_error(cmd->args[i]);
		else
			unset_env_var(&env, cmd->args[i]);
		i++;
	}
	return (ret);
}
