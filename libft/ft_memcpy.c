/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:22:43 by ttamae            #+#    #+#             */
/*   Updated: 2025/07/24 19:22:44 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	i = 0;
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
