/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:34:39 by alex              #+#    #+#             */
/*   Updated: 2025/04/21 21:49:32 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	space_proc(t_pipex *data, int index, int *end)
{
	if (data->fd_infile == -1 && index == 0)
		return (free(data->child_tab), close(end[1]), close(end[0]), exit(1));
	close(end[0]);
	dup2(end[1], 1);
	close(end[1]);
}

int	ft_is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] > 32 && str[i] < 127))
			return (0);
		i++;
	}
	return (1);
}

int	loop_here_doc(char *delimiter, int *end)
{
	char	*line;

	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(end[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	return (1);
}

int	here_doc_proc(char *delimiter)
{
	int	end[2];

	if (pipe(end) == -1)
		return (0);
	loop_here_doc(delimiter, end);
	dup2(end[0], 0);
	close(end[1]);
	close(end[0]);
	return (1);
}
