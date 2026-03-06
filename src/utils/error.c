/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 15:52:41 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/03/06 04:17:36 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	error_command_not_found(char *args)
{
	if (args)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	return (1);
}

int	error_fork()
{
	ft_putstr_fd("minishell: fork error\n", 2);
	return (1);
}
