/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:58:43 by ttamae            #+#    #+#             */
/*   Updated: 2025/07/24 19:58:44 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *lit, size_t len)
{
	size_t	i;
	size_t	j;

	if (*lit == '\0')
		return ((char *)big);
	i = 0;
	while (i < len && big[i] != '\0')
	{
		if (big[i] == lit[0])
		{
			j = 0;
			while ((i + j) < len && lit[j] != '\0' && big[i + j] == lit[j])
				j++;
			if (lit[j] == '\0')
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}
