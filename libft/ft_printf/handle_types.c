/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 20:04:49 by ttamae            #+#    #+#             */
/*   Updated: 2025/08/29 20:04:55 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	handle_char(va_list args)
{
	char	c;

	c = (char)va_arg(args, int);
	ft_putchar_fd(c, 1);
	return (1);
}

int	handle_string(va_list args)
{
	char	*str;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	handle_int(va_list args)
{
	char	*str;
	int		len;

	str = ft_itoa(va_arg(args, int));
	if (!str)
		return (0);
	ft_putstr_fd(str, 1);
	len = ft_strlen(str);
	free(str);
	return (len);
}

int	handle_unsigned(va_list args)
{
	char			*str;
	unsigned int	n;
	int				len;

	n = va_arg(args, unsigned int);
	str = ft_utoa(n);
	if (!str)
		return (0);
	ft_putstr_fd(str, 1);
	len = ft_strlen(str);
	free(str);
	return (len);
}

int	handle_hex(va_list args, int uppercase)
{
	char			*str;
	unsigned int	n;
	int				len;

	n = va_arg(args, unsigned int);
	str = ft_utoa_hex(n, uppercase);
	if (!str)
		return (0);
	ft_putstr_fd(str, 1);
	len = ft_strlen(str);
	free(str);
	return (len);
}
