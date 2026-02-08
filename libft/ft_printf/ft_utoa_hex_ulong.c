/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_hex_ulong.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:43:32 by ttamae            #+#    #+#             */
/*   Updated: 2025/09/06 16:43:34 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*get_hex_digits(int uppercase)
{
	if (uppercase)
		return ("0123456789ABCDEF");
	else
		return ("0123456789abcdef");
}

static int	count_hex_digits_ulong(unsigned long n)
{
	int	count;

	count = 1;
	while (n >= 16)
	{
		n /= 16;
		count++;
	}
	return (count);
}

char	*ft_utoa_hex_ulong(unsigned long n, int uppercase)
{
	int		len;
	char	*str;
	char	*digits;

	len = count_hex_digits_ulong(n);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	digits = get_hex_digits(uppercase);
	while (len > 0)
	{
		len--;
		str[len] = digits[n % 16];
		n /= 16;
	}
	return (str);
}
