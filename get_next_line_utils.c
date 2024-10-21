/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcheron <jcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:47:18 by jcheron           #+#    #+#             */
/*   Updated: 2024/10/21 17:38:01 by jcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}

char	*read_file(int fd)
{
	char	*buffer;
	int		bytes_red;

	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	bytes_red = read(fd, buffer, BUFFER_SIZE);
	if (ft_strrchr(buffer, '\n'))
		printf("%s", "saut");
	if (bytes_red <= 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}
