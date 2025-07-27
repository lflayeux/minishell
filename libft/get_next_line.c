/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:05:49 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/27 19:51:09 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_read(char *full_buf, int fd)
{
	int		byte_read;
	char	*buf;

	if (full_buf == NULL)
		full_buf = ft_calloc_gnl(1, sizeof(char));
	buf = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	if (!full_buf || !buf)
		return (NULL);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read < 0 || buf == NULL)
			return (free(full_buf), free(buf), NULL);
		buf[byte_read] = '\0';
		full_buf = ft_realloc_gnl(full_buf, buf);
		if (full_buf == NULL)
			return (NULL);
		if (ft_strchr_split(full_buf, '\n'))
			break ;
	}
	free(buf);
	return (full_buf);
}

char	*ft_line(char *full_buf)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	if (!full_buf[i])
		return (NULL);
	while (full_buf[i] != '\n' && full_buf[i])
		i++;
	line = ft_calloc_gnl((i + 2), 1);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (full_buf[i] != '\n' && full_buf[i])
		line[j++] = full_buf[i++];
	if (full_buf[i] == '\n' && full_buf[i])
		line[j] = '\n';
	return (line);
}

char	*ft_stay(char *full_buf)
{
	char	*stay;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (full_buf[i] && full_buf[i] != '\n')
		i++;
	if (full_buf[i] == '\n')
		i++;
	if (!full_buf[i])
	{
		free(full_buf);
		return (NULL);
	}
	while (full_buf[i + len])
		len++;
	stay = ft_calloc_gnl(len + 1, 1);
	if (stay == NULL)
		return (NULL);
	len = 0;
	while (full_buf[i])
		stay[len++] = full_buf[i++];
	free(full_buf);
	return (stay);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*full_buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	full_buf = ft_read(full_buf, fd);
	if (full_buf == NULL)
		return (NULL);
	line = ft_line(full_buf);
	full_buf = ft_stay(full_buf);
	return (line);
}
