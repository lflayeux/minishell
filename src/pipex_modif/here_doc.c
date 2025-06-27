/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:34:39 by alex              #+#    #+#             */
/*   Updated: 2025/06/27 20:21:12 by aherlaud         ###   ########.fr       */
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
	if (!line)
		return (0);
	while (line)
	{
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\n')
		{
			free(line);
			break ;
		}
		if (end)
			write(end[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
		if (!line)
		{
			ft_printf("EOF before delimiter '%s' is reached\n", delimiter);
			break ;
		}
	}
	return (1);
}

int	here_doc_proc(t_shell *shell, t_exec *exec, int *end)
{
	pid_t	child;
	int		status;

	parent_ignore(shell->signals);
	child = fork();
	if (child < 0)
		return (FALSE);
	if (child == 0)
	{
		child_signals(shell->signals);
		loop_here_doc(exec->delimiter, end);
		close_fd(shell);
		exit(0);
	}
	if (child > 0)
	{
		if (waitpid(child, &status, 0) == -1)
			return (FALSE);
		if (WEXITSTATUS(status) == 130)
			return (FALSE);
		parent_signals(shell->signals);
	}
	return (TRUE);
}

void	close_fd(t_shell *shell)
{
	if (PIPEX->end[0] != NONE && PIPEX->end[0] != -1)
		close(PIPEX->end[0]);
	if (PIPEX->end[1] != NONE && PIPEX->end[1] != -1)
		close(PIPEX->end[1]);
}

void	init_fd(t_shell *shell)
{
	PIPEX->end[0] = NONE;
	PIPEX->end[1] = NONE;
}
