/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:23:59 by ttamae            #+#    #+#             */
/*   Updated: 2025/07/24 19:24:00 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lend;
	size_t	lens;
	size_t	i;

	lend = ft_strlen(dst);
	lens = ft_strlen(src);
	i = 0;
	if (size <= lend)
		return (size + lens);
	while (src[i] && (lend + i + 1 < size))
	{
		dst[lend + i] = src[i];
		i++;
	}
	dst[lend + i] = '\0';
	return (lend + lens);
}
