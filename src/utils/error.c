/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:52:41 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/03/14 02:02:02 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_command_not_found(char *args)
{
	if (args)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(args, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	return (1);
}

int	error_fork(void)
{
	ft_putstr_fd("minishell: fork error\n", STDERR_FILENO);
	return (1);
}
