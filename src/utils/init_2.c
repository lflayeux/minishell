/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:31:53 by pandemonium       #+#    #+#             */
/*   Updated: 2025/08/01 18:47:45 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// INITIALISATION POUR L'EXEC ENTRE L'HERE_DOC
// (GESTION AVEC PIPE) OU L'INFILE SI IL Y A

int	infile_found(t_exec *exec, t_shell *shell)
{
	int	fd_infile;

	fd_infile = open((exec->infile), O_RDONLY);
	if (fd_infile == -1)
		return (FALSE);
	if ((shell->pipex)->prev_fd != NONE)
		close((shell->pipex)->prev_fd);
	(shell->pipex)->prev_fd = fd_infile;
	return (TRUE);
}

int	task_init(t_exec *exec, t_shell *shell)
{
	init_fd(shell);
	if (exec->if_here_doc == TRUE)
	{
		if ((shell->pipex)->prev_fd != NONE)
			close((shell->pipex)->prev_fd);
		(shell->pipex)->prev_fd = exec->end[0];
		close(exec->end[1]);
	}
	if (exec->if_infile == TRUE)
	{
		if (infile_found(exec, shell) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

void	exec_init(t_exec *node_exec)
{
	node_exec->cmd = NULL;
	node_exec->infile = NULL;
	node_exec->outfile = NULL;
	node_exec->end[0] = NONE;
	node_exec->end[1] = NONE;
	node_exec->if_infile = 0;
	node_exec->if_outfile = 0;
	node_exec->if_append = 0;
	node_exec->if_here_doc = 0;
	node_exec->if_quit = 0;
	node_exec->pipe_to = NULL;
}

void	init_fd(t_shell *shell)
{
	(shell->pipex)->end[0] = NONE;
	(shell->pipex)->end[1] = NONE;
}

void	init_pipex(t_shell *shell)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (free_error(shell));
	(shell->pipex) = pipex;
	(shell->pipex)->child_tab = NULL;
	(shell->pipex)->child_index = 0;
	(shell->pipex)->prev_fd = NONE;
	init_fd(shell);
}
