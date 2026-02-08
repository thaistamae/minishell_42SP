/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 19:38:36 by ttamae            #+#    #+#             */
/*   Updated: 2025/08/29 19:38:38 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	process_format(char a, va_list args)
{
	if (a == 'c')
		return (handle_char(args));
	else if (a == 's')
		return (handle_string(args));
	else if (a == 'p')
		return (handle_pointer(args));
	else if (a == 'd' || a == 'i')
		return (handle_int(args));
	else if (a == 'u')
		return (handle_unsigned(args));
	else if (a == 'x')
		return (handle_hex(args, 0));
	else if (a == 'X')
		return (handle_hex(args, 1));
	else if (a == '%')
	{
		ft_putstr_fd("%", 1);
		return (1);
	}
	return (0);
}
