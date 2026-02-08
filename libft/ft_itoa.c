/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:50:09 by ttamae            #+#    #+#             */
/*   Updated: 2025/08/01 19:50:10 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	count;

	if (n <= 0)
		count = 1;
	else
		count = 0;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		len;
	long	nb;
	char	*str;

	len = count_digits(n);
	nb = n;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		str[0] = '0';
	while (nb > 0)
	{
		len --;
		str[len] = '0' + (nb % 10);
		nb /= 10;
	}
	return (str);
}
