/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:31:53 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/13 17:18:55 by lflayeux         ###   ########.fr       */
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
	{
		if (access(exec->infile, F_OK) == -1)
			return (print_error(exec->infile, FILE_MESS, shell, 1), 0);
		else
			return (print_error(exec->infile, PERM, shell, 1), 0);
	}
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
		if (pipe((shell->pipex)->end) == -1)
			return (FALSE);
		if ((shell->pipex)->prev_fd != NONE)
			close((shell->pipex)->prev_fd);
		here_doc_pipe(exec, shell);
		(shell->pipex)->prev_fd = (shell->pipex)->end[0];
		close((shell->pipex)->end[1]);
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
	node_exec->here_doc = NULL;
	node_exec->if_infile = 0;
	node_exec->if_outfile = 0;
	node_exec->if_append = 0;
	node_exec->if_here_doc = 0;
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
