/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:34:39 by alex              #+#    #+#             */
/*   Updated: 2025/07/01 14:32:18 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//  MANAGEMENT DE L'OUTFILE/APPEND DANS UN CHILD SI PRESENT SINON PIPE
int	outfile_management(t_exec *exec, int *end, t_shell *shell)
{
	int	fd_outfile;

	fd_outfile = TRUE;
	if (exec->if_outfile == TRUE || exec->if_append == TRUE)
	{
		close_fd(shell, 2, 0);
		if (exec->if_outfile == TRUE)
			fd_outfile = open((exec->outfile), O_WRONLY | O_TRUNC | O_CREAT,
					0666);
		else
			fd_outfile = open((exec->outfile), O_WRONLY | O_CREAT | O_APPEND,
					0666);
		if (fd_outfile == ERROR)
			return (print_error(exec->outfile, FILE_MESS, shell, N_FOUND),
				FALSE);
		if (dup2(fd_outfile, STDOUT_FILENO) == ERROR)
			return (FALSE);
		close_fd(shell, 3, fd_outfile);
	}
	else
	{
		close_fd(shell, 0, 0);
		if (exec->pipe_to != NULL)
		{
			if (dup2(end[1], 1) == ERROR)
				return (FALSE);
			close_fd(shell, 1, 0);
		}
	}
	return (TRUE);
}

//  MANAGEMENT IN PARENT PROCESS IF END OF EXEC STRUCT OR NEXT PIPE
int	end_or_pipe(t_exec *exec, pid_t child, int *end, t_shell *shell)
{
	int	i;
	int	status;

	// if (exec->cmd[0])
	if (exec->pipe_to == NULL)
	{
		i = 0;
		if (PIPEX->prev_fd != NONE)
			close(PIPEX->prev_fd);
		while (PIPEX->child_tab[i])
		{
			if (waitpid(PIPEX->child_tab[i++], &status, 0) == -1)
				return (/*exit_status(status, shell),*/ FALSE);
		}
		if (waitpid(child, &status, 0) == -1)
			return (/*exit_status(status, shell),*/ FALSE);
	}
	else
	{
		close_fd(shell, 1, 0);
		if (PIPEX->prev_fd != NONE)
			close(PIPEX->prev_fd);
		PIPEX->prev_fd = end[0];
		PIPEX->child_tab[PIPEX->child_index] = child;
	}
	return (TRUE);
}

// MAIN MANAGEMENT OF THE CHILD EXEC PROCESS (CREATTION OF CHILD, PIPE,
// PROCESS REDIRECTION)
int	middle_proc(t_exec *exec, t_shell *shell)
{
	pid_t	child;

	init_fd(shell);
	if (exec->pipe_to)
	{
		if (pipe(PIPEX->end) == -1)
			return (FALSE);
	}
	child = fork();
	if (child < 0)
		return (close_fd(shell, 2, 0), FALSE) ;
	else if (child == 0)
	{
		child_signals(shell->signals);
		// if (task_init(exec, shell) == FALSE)
		// 	return (FALSE);
		if (PIPEX->prev_fd != NONE && PIPEX->prev_fd != STDIN_FILENO)
		{
			if (dup2(PIPEX->prev_fd, STDIN_FILENO) == -1)
				return (FALSE);
			close(PIPEX->prev_fd);
			// PIPEX->prev_fd = NONE;
		}
		outfile_management(exec, PIPEX->end, shell);
		if (!exec->cmd || !exec->cmd[0])
		{
			close_fd(shell, 2, 0);
			free_all(shell);
			exit(0);
		}
		exec_cmd(exec->cmd, shell);
	}
	else
	{
		parent_signals(shell->signals);
		end_or_pipe(exec, child, PIPEX->end, shell);
	}
	return (TRUE);
}

/**
	CALCUL DU NOMBRE DE NODE DANS LA LISTE CHAINEE POUR AVOIR LE NOMBRE DE PROCESS À WAIT

	@param lst_exec La liste chaine sur laquelle on compte

	@return			Le nombre de node dans la liste chainee. 0 si pas de liste chainee

*/
int	node_number(t_exec *lst_exec)
{
	t_exec	*tmp;
	int		len;

	if (!lst_exec)
		return (0);
	tmp = lst_exec;
	len = 0;
	while (tmp)
	{
		tmp = tmp->pipe_to;
		len++;
	}
	return (len);
}

// INITIALISATION POUR L'EXEC ENTRE L'HERE_DOC (GESTION AVEC PIPE) OU L'INFILE SI IL Y A
int	task_init(t_exec *exec, t_shell *shell)
{
	int	fd_infile;

	init_fd(shell);
	if (exec->if_here_doc == TRUE)
	{
		if (pipe(PIPEX->end) == -1)
			return (FALSE);
		if (exec->cmd[0] && exec->cmd)
		{
			if (here_doc_proc(shell, exec, PIPEX->end) == FALSE)
				return (FALSE);
		}
		else
		{
			if (here_doc_proc(shell, exec, NULL) == FALSE)
				return (FALSE);
		}
		PIPEX->prev_fd = PIPEX->end[0];
		close(PIPEX->end[1]);
		// close_fd(shell);
	}
	if (exec->if_infile == TRUE)
	{
		fd_infile = open((exec->infile), O_RDONLY);
		if (fd_infile == -1)
			return (FALSE);
		PIPEX->prev_fd = fd_infile;
	}
	// if (exec->if_here_doc == FALSE && exec->if_infile == FALSE)
	return (TRUE);
}

// GESTION DE LA BOUCLE DE TOUTES LES EXECS À FAIRE ET INIT TU TABLEAU DE CHILD À WAIT
int	pipex(t_shell *shell)
{
	t_exec	*tmp;

	PIPEX->child_tab = ft_calloc(node_number(shell->exec) + 1, sizeof(pid_t));
	if (!(PIPEX->child_tab))
		return (print_error("malloc", NULL, shell, GEN_ERROR), FALSE);
	PIPEX->child_tab[node_number(shell->exec)] = '\0';
	tmp = shell->exec;
	while (tmp)
	{
		// check si commande vide
		if (built_in(tmp, shell) == FALSE)
		{
			if (task_init(tmp, shell) == FALSE)
				break;
			// parent_signals(shell->signals);
			if (tmp->cmd && tmp->cmd[0] && ft_strcmp((tmp->cmd)[0], "") == 0)
				return (print_error(" ", N_CMD_MESS, shell, N_FOUND), TRUE);
			middle_proc(tmp, shell);
		}
		tmp = tmp->pipe_to;
	}
	if (PIPEX->child_tab)
		free(PIPEX->child_tab);
	PIPEX->child_tab = NULL;
	return (TRUE);
}
