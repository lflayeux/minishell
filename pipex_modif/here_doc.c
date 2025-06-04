/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:34:39 by alex              #+#    #+#             */
/*   Updated: 2025/06/04 11:09:29 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	if(!line)
		return (0);
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
		if(!line)
			return (0);
	}
	if (line)
		free(line);
	return (1);
}

void	close_fd(t_shell *shell)
{
	if (shell->end[0] != 999 && shell->end[0] != -1)
		close(shell->end[0]);
	if (shell->end[1] != 999 && shell->end[1] != -1)
		close(shell->end[1]);
}

void	init_fd(t_shell *shell)
{
	shell->end[0] = 999;
	shell->end[1] = 999;
}
