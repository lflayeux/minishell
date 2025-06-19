/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:34:39 by alex              #+#    #+#             */
/*   Updated: 2025/06/19 23:14:06 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//  MANAGEMENT DE L'OUTFILE/APPEND DANS UN CHILD SI PRESENT SINON PIPE
int	outfile_management(t_exec *exec, int *end, t_shell *shell)
{
	int	fd_outfile;

	fd_outfile = 1;
	if (exec->if_outfile == 1 || exec->if_append == 1)
	{
		close(end[1]);
		close(end[0]);
		if (exec->if_outfile == TRUE)
			fd_outfile = open((exec->outfile), O_WRONLY | O_TRUNC | O_CREAT,
					0666);
		else
			fd_outfile = open((exec->outfile), O_WRONLY | O_CREAT | O_APPEND,
					0666);
		if (fd_outfile == -1)
			return (FALSE);
		if (dup2(fd_outfile, STDOUT_FILENO) == -1)
			return (FALSE);
		close(fd_outfile);
	}
	else
	{
		close(end[0]);
		if (exec->pipe_to != NULL)
		{
			if(dup2(end[1], 1) == -1)
				return (FALSE);
			close(end[1]);
		}
	}
	return (TRUE);
}

//  MANAGEMENT IN PARENT PROCESS IF END OF EXEC STRUCT OR NEXT PIPE
int	end_or_pipe(t_exec *exec, pid_t child, int *end, t_shell *shell)
{
	int	i;

	if (exec->pipe_to == NULL)
	{
		i = 0;
		while (shell->child_tab[i])
		{
			if (waitpid(shell->child_tab[i++], NULL, 0) == -1)
				return (free_exit(shell));
		}
		if (waitpid(child, NULL, 0) == -1)
			return (free_exit(shell));
	}
	else
	{
		close(end[1]);
		// if (close(end[1]) == -1)
		// 	return (ft_free_all(shell), exit(1), 0);
		shell->prev_fd = end[0];
		shell->child_tab[shell->child_index] = child;
	}
	return (1);
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
		return (close_fd(shell), FALSE);
	else if (child == 0)
	{
		if (PIPEX->prev_fd != STDIN_FILENO)
		{
			if(dup2(PIPEX->prev_fd, STDIN_FILENO) == -1)
				return (FALSE);
			close(PIPEX->prev_fd);
		}
		outfile_management(exec, PIPEX->end, shell);
		exec_cmd(exec->cmd, shell);
	}
	else
		end_or_pipe(exec, child, shell->end, shell);
	return (1);
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
			return FALSE;
		if (loop_here_doc(exec->delimiter, PIPEX->end) == FALSE)
			return (FALSE);
		PIPEX->prev_fd = PIPEX->end[0];
		close_fd(shell);
	}
	if (exec->if_infile == TRUE)
	{
		fd_infile = open((exec->infile), O_RDONLY);
		if (fd_infile == -1)
			return (FALSE);
		PIPEX->prev_fd = fd_infile;
	}
}

// GESTION DE LA BOUCLE DE TOUTES LES EXECS À FAIRE ET INIT TU TABLEAU DE CHILD À WAIT
int	pipex(t_shell *shell)
{
	t_exec	*tmp;

	PIPEX->child_tab = ft_calloc(node_number(shell->exec) + 1, sizeof(pid_t));
	if (!(PIPEX->child_tab))
		return (print_error(shell, MALLOC), FALSE);
	tmp = shell->exec;
	while (tmp)
	{
		// check si commande vide
		if(ft_strcmp((tmp->cmd)[0], "") == 0)
			return (ft_printf("Command '' not found"), TRUE);
		if (task_init(tmp, shell) == FALSE)
			return (FALSE);
		middle_proc(tmp, shell);
		tmp = tmp->pipe_to;
	}
	return (TRUE);
}
