/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 10:54:04 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/03/26 23:53:24 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(void)
{
	char	buffer[4096];

	if (!getcwd(buffer, sizeof(buffer)))
	{
		perror("minishell: pwd");
		return (1);
	}
	ft_putstr_fd(buffer, STDOUT_FILENO);
	return (0);
}
