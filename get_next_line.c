/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:33:15 by jcheron           #+#    #+#             */
/*   Updated: 2024/10/21 22:06:19 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

static char	*ft_keep_rest(char *buffer)
{
	int		i;
	int		j;
	char	*rest;

	i = ft_find_newline(buffer);
	if (i == -1)
	{
		free(buffer);
		return (NULL);
	}
	rest = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!rest)
		return (NULL);
	j = 0;
	while (buffer[i + 1])
		rest[j++] = buffer[++i];
	rest[j] = '\0';
	free(buffer);
	return (rest);
}

static char	*ft_get_line(char *buffer)
{
	int		i;
	char	*line;

	i = ft_find_newline(buffer);
	if (i == -1)
		i = ft_strlen(buffer);
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	ft_strlcpy(line, buffer, i + 1);
	return (line);
}

static int	read_buffer(int fd, char **rest)
{
	char		*buffer;
	int			bytes_read;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1)
	{
		free(buffer);
		return (-1);
	}
	buffer[bytes_read] = '\0';
	*rest = ft_strjoin(*rest, buffer);
	free(buffer);
	return (bytes_read);
}

static char	*process_line(char **rest)
{
	char	*line;

	if (!*rest || !**rest)
	{
		free(*rest);
		*rest = NULL;
		return (NULL);
	}
	line = ft_get_line(*rest);
	*rest = ft_keep_rest(*rest);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = 1;
	while (ft_find_newline(rest) == -1 && bytes_read > 0)
	{
		bytes_read = read_buffer(fd, &rest);
		if (bytes_read == -1)
			return (NULL);
	}
	return (process_line(&rest));
}

// int main(void)
// {
// 	int		fd;
// 	char	*line;

// 	printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
// 	fd = open("test", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("Error opening file\n");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("Line : %s\n", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
