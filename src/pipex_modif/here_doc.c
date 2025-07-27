/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:34:39 by alex              #+#    #+#             */
/*   Updated: 2025/07/27 19:06:24 by aherlaud         ###   ########.fr       */
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

int	stock_here_doc(char *delimiter, char **big_line, t_shell *shell)
{
	char	*line;
	char	*del_join;

	del_join = ft_strjoin(delimiter, "\n");
	if (!del_join)
		free_error(shell);
	// free_all(shell);
	while (1)
	{
		// line = get_next_line(0);
		// dup2(end[1], 0);
		line = readline("> ");
		// if (g_signal_global == 130)
		// 	return (free(*big_line), free(del_join), free_all(shell), exit(130), FALSE);
		// free(line);
		if (!line)
		{
			// write(1, "EOF before delimiter '%s' is reached\n", 37);
			printf("EOF before delimiter '%s' is reached\n", delimiter);
			return (free(line), free(del_join), TRUE);
		}
		line = ft_strjoin_free(line, "\n", shell);
		if (ft_strcmp(line, del_join) == 0)
			return (free(line), free(del_join), TRUE);
		if (*big_line != NULL)
			*big_line = ft_strjoin_free(*big_line, " ", shell);
		*big_line = ft_strjoin_free(*big_line, line, shell);
		free(line);
	}
	free(del_join);
	return (TRUE);
}

int	here_doc_pipe(char *delimiter, t_exec *exec, t_shell *shell)
{
	int	i;
	char	*big_line;
	char	**tab;

	i = 0;
	big_line = NULL;
	// dup2(exec->end[1], 0);
	if (stock_here_doc(delimiter, &big_line, shell) == FALSE)
		return (FALSE);
	if (!big_line)
		return (FALSE);
	tab = ft_split(big_line, ' ');
	free(big_line);
	if (!tab)
		free_error(shell);
	while (tab && tab[i])
	{
		write(exec->end[1], tab[i], ft_strlen(tab[i]));
		i++;
	}
	close(exec->end[1]);
	return (TRUE);
}

int loop_here_doc(t_exec *node_exec, char *delimiter, t_shell *shell)
{
	// char	*big_line;
	// char	**tab;
	pid_t child;
	int status;

	child = fork();
	status = 0;
	if(child < 0)
		free_error(shell);
	else if(child == 0)
	{
		close(node_exec->end[0]);
		here_doc_signals(shell->signals);
		here_doc_pipe(delimiter, node_exec, shell);
		// if (g_signal_global == 130)
		// 	exit(130);
		// else
		free_all(shell);
		exit(0);
		// big_line = NULL;
		// if (stock_here_doc(delimiter, &big_line, shell) == FALSE)
		// 	return (FALSE);
		// if (!big_line)
		// 	return (FALSE);
		// tab = ft_split(big_line, ' ');
		// free(big_line);
		// if (!tab)
		// 	free_error(shell);
	}
	else
	{
		waitpid(child, &status, 0);
		if (WIFEXITED(status))
		{
			g_signal_global = WEXITSTATUS(status);
			if (g_signal_global == 130)
				return (close(node_exec->end[0]), close(node_exec->end[1]), FALSE);
		}
	}
	return (TRUE);
}

void	close_fd(t_shell *shell, int fd, int to_close)
{
	if (fd == 0 && (shell->pipex)->end[0] >= 0
		&& (shell->pipex)->end[0] != NONE)
	{
		close((shell->pipex)->end[0]);
		(shell->pipex)->end[0] = NONE;
	}
	if (fd == 1 && (shell->pipex)->end[1] >= 0
		&& (shell->pipex)->end[1] != NONE)
	{
		close((shell->pipex)->end[1]);
		(shell->pipex)->end[1] = NONE;
	}
	if (fd == 2 && (shell->pipex)->end[0] >= 0 && (shell->pipex)->end[1] >= 0
		&& (shell->pipex)->end[1] != NONE && (shell->pipex)->end[0] != NONE)
	{
		close((shell->pipex)->end[1]);
		close((shell->pipex)->end[0]);
		init_fd(shell);
	}
	if (fd == 3 && to_close >= 0 && to_close != NONE)
	{
		close(to_close);
	}
}
