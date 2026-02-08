/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamae <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 14:36:01 by ttamae            #+#    #+#             */
/*   Updated: 2025/09/27 14:36:04 by ttamae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*extract_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (!stash || stash[0] == '\0')
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*update_stash(char	*stash)
{
	size_t	i;
	size_t	j;
	char	*updated;

	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\0')
		return (NULL);
	i++;
	updated = malloc((ft_strlen(stash + i)) + 1);
	if (!updated)
		return (NULL);
	j = 0;
	while (stash[i])
	{
		updated[j] = stash[i];
		i++;
		j++;
	}
	updated[j] = '\0';
	return (updated);
}

static char	*read_to_stash(int fd, char	*stash)
{
	char	*buffer;
	char	*tmp;
	int		bytes_read;

	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}	
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(stash, buffer);
		free(stash);
		stash = tmp;
		free(buffer);
	}	
	return (stash);
}

char	*get_next_line(int fd)
{
	static char		*stash;
	char			*line;
	char			*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	stash = read_to_stash(fd, stash);
	if (!stash || stash[0] == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = extract_line(stash);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	tmp = update_stash(stash);
	free(stash);
	stash = tmp;
	return (line);
}
