/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 19:39:02 by ttamae            #+#    #+#             */
/*   Updated: 2025/08/29 19:39:03 by ttamae           ###   ########.fr       */
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

static int	count_hex_digits(unsigned int n)
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

char	*ft_utoa_hex(unsigned int n, int uppercase)
{
	int		len;
	char	*str;
	char	*digits;

	len = count_hex_digits(n);
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
