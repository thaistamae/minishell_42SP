/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 13:45:41 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/04/08 22:55:38 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(char *s)
{
	int	i;

	if (!s || !s[0] || (!ft_isalpha((unsigned char)s[0]) && s[0] != '_'))
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

char	*get_valid_key(char *arg, char **eq)
{
	char	*key;

	*eq = ft_strchr(arg, '=');
	if (*eq)
		key = ft_substr(arg, 0, *eq - arg);
	else
		key = ft_strdup(arg);
	if (!key)
		return (NULL);
	if (!is_valid_identifier(key))
	{
		free(key);
		return (NULL);
	}
	return (key);
}

int	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (1);
}
