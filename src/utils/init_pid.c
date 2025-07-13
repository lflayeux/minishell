/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:42:21 by aherlaud          #+#    #+#             */
/*   Updated: 2025/07/13 16:57:47 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pid_line(t_shell *shell, int fd, char *line)
{
	char	**split;
	char	*tmp;

	split = ft_split(line, '\t');
	if (!split)
		return (close(fd), free(line), free_error(shell));
	tmp = ft_substr(split[1], 0, ft_strlen(split[1]) - 1);
	if (!tmp)
		return (free(line), ft_free_tab((void **)split), free_error(shell));
	shell->pid = tmp;
	ft_free_tab((void **)split);
}

void	get_pid(t_shell *shell)
{
	int		fd;
	char	*line;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd == -1)
		return (free_error(shell));
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "Pid:", 4) == 0)
			pid_line(shell, fd, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
