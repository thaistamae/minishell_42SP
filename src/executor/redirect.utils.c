/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaidda-s <kaidda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 20:17:05 by kaidda-s          #+#    #+#             */
/*   Updated: 2026/03/09 20:48:04 by kaidda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirect(char *cmd)
{
	if (!ft_strncmp(cmd, ">", 2))
		return (1);
	if (!ft_strncmp(cmd, "<", 2))
		return (1);
	if (!ft_strncmp(cmd, ">>", 3))
		return (1);
	if (!ft_strncmp(cmd, "<<", 3))
		return (1);
}

