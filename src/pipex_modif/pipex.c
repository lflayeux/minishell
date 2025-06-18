/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:34:39 by alex              #+#    #+#             */
/*   Updated: 2025/06/18 16:06:57 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//  MANAGEMENT DE L'OUTFILE/APPEND DANS UN CHILD SI PRESENT SINON PIPE
int	outfile_management(t_exec *exec, int *end, t_shell *shell)
{
	int	fd_outfile;

	fd_outfile = 1;
	(void)shell;
	if (exec->if_outfile == 1 || exec->if_append == 1)
	{
		close(end[1]);
		close(end[0]);
		if (exec->if_outfile == 1)
			fd_outfile = open((exec->outfile), O_WRONLY | O_TRUNC | O_CREAT,
					0666);
		else
			fd_outfile = open((exec->outfile), O_WRONLY | O_CREAT | O_APPEND,
					0666);
		if (fd_outfile == -1)
			return (free_exit(shell));
		if (dup2(fd_outfile, STDOUT_FILENO) == -1)
			free_exit(shell);
		close(fd_outfile);
	}
	else
	{
		close(end[0]);
		if (exec->pipe_to != NULL)
		{
			if(dup2(end[1], 1) == -1)
				free_exit(shell);
			close(end[1]);
		}
	}
	return (1);
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
		if (pipe(shell->end) == -1)
			free_exit(shell);
	}
	child = fork();
	if (child < 0)
		return (close_fd(shell), free_exit(shell));
	else if (child == 0)
	{
		if (shell->prev_fd != STDIN_FILENO)
		{
			if(dup2(shell->prev_fd, STDIN_FILENO) == -1)
				free_exit(shell);
			close(shell->prev_fd);
		}
		outfile_management(exec, shell->end, shell);
		// good pour les malloc exec
		exec_cmd(exec->cmd, shell);
		// if (exec_cmd(exec->cmd, shell) == 0)
		// 	return (close(end[1]), exit(EXIT_FAILURE), 0);
	}
	// error good
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
void	task_init(t_exec *exec, t_shell *shell)
{
	int	fd_infile;

	init_fd(shell);
	if (exec->if_here_doc == 1)
	{
		if (pipe(shell->end) == -1)
			free_exit(shell);
		if (loop_here_doc(exec->delimiter, shell->end) == 0)
			free_exit(shell);
		shell->prev_fd = shell->end[0];
		close_fd(shell);
	}
	if (exec->if_infile == 1)
	{
		fd_infile = open((exec->infile), O_RDONLY);
		if (fd_infile == -1)
			free_exit(shell);
		shell->prev_fd = fd_infile;
	}
}

// GESTION DE LA BOUCLE DE TOUTES LES EXECS À FAIRE ET INIT TU TABLEAU DE CHILD À WAIT
int	pipex(t_shell *shell)
{
	t_exec	*tmp;

	// deja dans shell et free dans free_all
	shell->child_tab = ft_calloc(node_number(shell->exec) + 1, sizeof(pid_t));
	if (!(shell->child_tab))
		return (free_exit(shell), -1);
	tmp = shell->exec;
	while (tmp)
	{
		// check si commande vide
		if(ft_strcmp((tmp->cmd)[0], "") == 0)
			return (ft_printf("Command '' not found"),1);
		task_init(tmp, shell);
		// if(task_init(tmp, shell) == 0)
		// 	return (free_exit(shell));
		// printf("\t\t\t\t\t\t\t\t\t\t\tTEST\n");
		middle_proc(tmp, shell);
		// if (middle_proc(tmp, shell) == 0)
		// 	return (-1);
		tmp = tmp->pipe_to;
	}
	return (1);
}
