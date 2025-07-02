/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:34:39 by alex              #+#    #+#             */
/*   Updated: 2025/07/02 19:40:09 by aherlaud         ###   ########.fr       */
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

char	**loop_here_doc(char *delimiter)
{
	char	*line;
	char	*big_line;
	char	**tab;

	big_line = NULL;
	line = get_next_line(0);
	if (!line)
		return (FALSE);
	while (line)
	{
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\n')
		{
			free(line);
			break ;
		}
		if (big_line != NULL)
			big_line = ft_strjoin_free(big_line, " ");
		big_line = ft_strjoin_free(big_line, line);
		free(line);
		line = get_next_line(0);
		if (signal_global == 130)
			return (free(big_line), NULL);
		if (!line)
		{
			ft_printf("EOF before delimiter '%s' is reached\n", delimiter);
			break ;
		}
	}
	if (!big_line)
		return (NULL);
	tab = ft_split(big_line, ' ');
	free(big_line);
	return (tab);
}

// int	here_doc_proc(t_exec *exec, char *delimiter, t_shell *shell)
// {
// 	pid_t	child;
// 	int		status;

// 	parent_ignore(shell->signals);
// 	child = fork();
// 	if (child < 0)
// 		return (FALSE);
// 	if (child == 0)
// 	{
// 		child_signals(shell->signals);
// 		exec->here_doc = loop_here_doc(delimiter, shell);
// 		if (exec->here_doc == NULL && signal_global == 130)
// 			return (exit_here_doc(shell), FALSE);
// 		// close_fd(shell, 2, 0);
// 		free_all(shell);
// 		exit(0);
// 	}
// 	if (child > 0)
// 	{
// 		if (waitpid(child, &status, 0) == -1)
// 			return (FALSE);
// 		if (WEXITSTATUS(status) == 130)
// 			return (FALSE);
// 		parent_signals(shell->signals);
// 	}
// 	return (TRUE);
// }

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

void	init_fd(t_shell *shell)
{
	PIPEX->end[0] = NONE;
	PIPEX->end[1] = NONE;
}
