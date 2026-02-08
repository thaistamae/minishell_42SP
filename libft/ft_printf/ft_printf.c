/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 19:38:10 by ttamae            #+#    #+#             */
/*   Updated: 2025/08/29 19:38:16 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	print_count(char c, int *count)
{
	ft_putchar_fd(c, 1);
	(*count)++;
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] != '%')
			print_count(format[i], &count);
		else
		{
			if (format[i + 1])
			{
				i++;
				count += process_format(format[i], args);
			}
			else
				print_count('%', &count);
		}
		i++;
	}
	va_end(args);
	return (count);
}
