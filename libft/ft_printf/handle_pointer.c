/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:04:49 by ttamae            #+#    #+#             */
/*   Updated: 2025/08/29 20:04:55 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	handle_pointer(va_list args)
{
	void	*ptr;
	char	*str;
	int		len;

	ptr = va_arg(args, void *);
	if (!ptr)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	str = ft_utoa_hex_ulong((unsigned long)ptr, 0);
	if (!str)
		return (0);
	ft_putstr_fd("0x", 1);
	ft_putstr_fd(str, 1);
	len = ft_strlen(str) + 2;
	free(str);
	return (len);
}
