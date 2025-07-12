/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:34:39 by alex              #+#    #+#             */
/*   Updated: 2025/07/12 20:39:42 by aherlaud         ###   ########.fr       */
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

int	stock_here_doc(char *delimiter, char **big_line, char **line)
{
	while (*line)
	{
		free(*line);
		*line = get_next_line(0);
		if (g_signal_global == 130)
			return (free(*big_line), FALSE);
		if (!*line)
		{
			ft_printf("EOF before delimiter '%s' is reached\n", delimiter);
			break ;
		}
		if (ft_strlen(*line) == ft_strlen(delimiter) + 1 && ft_strncmp(*line, delimiter, ft_strlen(*line) - 1) == 0)
		{
			free(*line);
			break ;
		}
		if (*big_line != NULL)
			*big_line = ft_strjoin_free(*big_line, " ");
		*big_line = ft_strjoin_free(*big_line, *line);
	}
	return (TRUE);
}

char	**loop_here_doc(char *delimiter)
{
	char	*line;
	char	*big_line;
	char	**tab;

	big_line = NULL;
	line = malloc(1);
	if (!line)
		return (FALSE);
	if (stock_here_doc(delimiter, &big_line, &line) == FALSE)
		return (FALSE);
	if (!big_line)
		return (FALSE);
	tab = ft_split(big_line, ' ');
	free(big_line);
	return (tab);
}

int	here_doc_pipe(t_exec *exec, t_shell *shell)
{
	int	i;

	i = 0;
	while (exec->here_doc && exec->here_doc[i])
	{
		write(PIPEX->end[1], exec->here_doc[i], ft_strlen(exec->here_doc[i]));
		i++;
	}
	return (TRUE);
}

void	close_fd(t_shell *shell, int fd, int to_close)
{
	if (fd == 0 && PIPEX->end[0] >= 0 && PIPEX->end[0] != NONE)
	{
		close(PIPEX->end[0]);
		PIPEX->end[0] = NONE;
	}
	if (fd == 1 && PIPEX->end[1] >= 0 && PIPEX->end[1] != NONE)
	{
		close(PIPEX->end[1]);
		PIPEX->end[1] = NONE;
	}
	if (fd == 2 && PIPEX->end[0] >= 0 && PIPEX->end[1] >= 0
		&& PIPEX->end[1] != NONE && PIPEX->end[0] != NONE)
	{
		close(PIPEX->end[1]);
		close(PIPEX->end[0]);
		init_fd(shell);
	}
	if (fd == 3 && to_close >= 0 && to_close != NONE)
	{
		close(to_close);
	}
}
