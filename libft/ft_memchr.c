/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:59:16 by ttamae            #+#    #+#             */
/*   Updated: 2025/07/24 19:59:17 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ptr;
	unsigned char		uc;

	uc = (unsigned char)c;
	i = 0;
	ptr = (const unsigned char *)s;
	while (i < n)
	{
		if (ptr[i] == uc)
		{
			return ((void *)(ptr + i));
		}
		i++;
	}
	return (NULL);
}
