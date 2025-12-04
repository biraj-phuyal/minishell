/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 06:39:06 by gude-and          #+#    #+#             */
/*   Updated: 2024/10/09 15:47:14 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*update_buffer(char *buffered)
{
	char	*new_buffer;
	int		i;
	int		j;

	i = 0;
	while (buffered[i] && buffered[i] != '\n')
		i++;
	if (!buffered[i])
	{
		free(buffered);
		return (NULL);
	}
	new_buffer = malloc(ft_strlen(buffered) - i);
	if (!new_buffer)
		return (NULL);
	i++;
	j = 0;
	while (buffered[i])
		new_buffer[j++] = buffered[i++];
	new_buffer[j] = '\0';
	free(buffered);
	return (new_buffer);
}

static char	*extract_line(char *buffered)
{
	char	*line;
	int		len;

	len = 0;
	if (!buffered[len])
		return (NULL);
	while (buffered[len] && buffered[len] != '\n')
		len++;
	line = malloc(len + 2);
	if (!line)
		return (NULL);
	len = 0;
	while (buffered[len] && buffered[len] != '\n')
	{
		line[len] = buffered[len];
		len++;
	}
	if (buffered[len] == '\n')
	{
		line[len] = '\n';
		len++;
	}
	line[len] = '\0';
	return (line);
}

static char	*read_and_append(int fd, char *buffered)
{
	char	*temp_buf;
	int		bytes_read;

	temp_buf = malloc(BUFFER_SIZE + 1);
	if (!temp_buf)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffered, '\n'))
	{
		bytes_read = read(fd, temp_buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(temp_buf);
			return (NULL);
		}
		temp_buf[bytes_read] = '\0';
		buffered = ft_strjoin(buffered, temp_buf);
	}
	free(temp_buf);
	return (buffered);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffered;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffered = read_and_append(fd, buffered);
	if (!buffered)
		return (NULL);
	line = extract_line(buffered);
	buffered = update_buffer(buffered);
	return (line);
}
