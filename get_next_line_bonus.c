/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:40:28 by jcheron           #+#    #+#             */
/*   Updated: 2024/10/27 14:38:55 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*_ft_strchr(char *s, int c)
{
	while (*s && *s != (char) c)
		s++;
	if (*s == (char) c)
		return ((char *) s);
	return (NULL);
}

static char	*_fill_line(int fd, char *filled, char *buffer)
{
	ssize_t	buffer_read;
	char	*temp;

	buffer_read = 1;
	while (buffer_read > 0)
	{
		buffer_read = read(fd, buffer, BUFFER_SIZE);
		if (buffer_read == -1)
		{
			free(filled);
			return (NULL);
		}
		else if (buffer_read == 0)
			break ;
		buffer[buffer_read] = 0;
		if (!filled)
			filled = ft_strdup("");
		temp = filled;
		filled = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (_ft_strchr(buffer, '\n'))
			break ;
	}
	return (filled);
}

static char	*_set_line(char *line_buffer)
{
	ssize_t	i;
	char	*line;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0 || line_buffer[1] == 0)
		return (NULL);
	line = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*line == 0)
	{
		free(line);
		line = NULL;
	}
	line_buffer[i + 1] = 0;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*old[FD_MAX];
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffer);
		free(old[fd]);
		buffer = NULL;
		old[fd] = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = _fill_line(fd, old[fd], buffer);
	free (buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	old[fd] = _set_line(line);
	return (line);
}
