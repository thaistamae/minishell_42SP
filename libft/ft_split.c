/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:49:34 by ttamae            #+#    #+#             */
/*   Updated: 2025/08/01 19:49:36 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*alloc_word(const char *start, size_t len)
{
	char	*word;
	size_t	i;

	word = malloc(len + 1);
	if (!word)
		return (0);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static int	store_word(char **result, char const *start_ptr, size_t len, int i)
{
	result[i] = alloc_word(start_ptr, len);
	if (!result[i])
	{
		while (--i >= 0)
			free(result[i]);
		return (0);
	}
	return (1);
}

static int	fill_words(char **result, char const *s, char c, int word_count)
{
	size_t	start;
	size_t	end;
	int		i;

	i = 0;
	end = 0;
	while (s[end] && i < word_count)
	{
		while (s[end] == c)
			end++;
		start = end;
		while (s[end] && s[end] != c)
			end++;
		if (end > start)
		{
			if (!store_word(result, s + start, end - start, i))
				return (0);
			i++;
		}
	}
	result[i] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	if (!fill_words(result, s, c, word_count))
	{
		free(result);
		return (NULL);
	}
	return (result);
}
