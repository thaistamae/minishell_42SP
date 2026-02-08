/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:25:29 by ttamae            #+#    #+#             */
/*   Updated: 2025/07/24 19:25:30 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*c_ptr;

	c_ptr = NULL;
	while (*s)
	{
		if (*s == (char)c)
		{
			c_ptr = (char *)s;
		}
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (c_ptr);
}
