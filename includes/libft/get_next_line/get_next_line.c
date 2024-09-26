/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:33:00 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/06/17 17:15:18 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_data_gnl(char *stash, char *buffer)
{
	free(stash);
	free(buffer);
	return (NULL);
}

char	*readlines(int fd, char *stash)
{
	char	*buffer;
	int		bytes;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (0);
	*buffer = 0;
	bytes = 1;
	while (bytes > 0 && !ft_strchr_gnl(buffer, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free_data_gnl(stash, buffer));
		buffer[bytes] = '\0';
		stash = ft_strjoin_gnl(stash, buffer);
	}
	if (*stash == '\0')
		return (free_data_gnl(stash, buffer));
	free(buffer);
	return (stash);
}

/// @brief Reads from fd line by line
/// @param fd File descriptor
/// @return Each line
char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			size;
	int			len_line;
	char		*stashtemp;

	if (!stash)
		stash = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = readlines(fd, stash);
	if (!stash)
		return (NULL);
	len_line = ft_strclen_gnl(stash, '\n');
	line = ft_strdup_gnl(stash, len_line + 1);
	if (!line)
		return (NULL);
	size = ft_strclen_gnl(stash, '\0') - len_line;
	stashtemp = stash;
	stash = ft_strdup_gnl(stash + len_line + 1, size);
	free (stashtemp);
	if (!stash)
		free(stash);
	return (line);
}
