/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:34:39 by alex              #+#    #+#             */
/*   Updated: 2025/05/25 23:45:15 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//  MANAGEMENT DE L'OUTFILE/APPEND DANS UN CHILD SI PRESENT SINON PIPE
int outfile_management(t_exec *exec, int *end)
{
	int fd_outfile;
	
	if (exec->if_outfile == 1 || exec->if_append == 1)
	{
		close(end[1]);
		close(end[0]);
		if (exec->if_outfile == 1)
			fd_outfile = open((exec->outfile), O_WRONLY | O_TRUNC | O_CREAT,
					0666);
		else
			fd_outfile = open((exec->outfile), O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd_outfile == -1)
			return (0);
		dup2(fd_outfile, STDOUT_FILENO);
		close(fd_outfile);
	}
	else
	{
		close(end[0]);
		dup2(end[1], 1);
		close(end[1]);
	}
	return (1);
}

//  MANAGEMENT IN PARENT PROCESS IF END OF EXEC STRUCT OR NEXT PIPE
int end_or_pipe(t_exec *exec, pid_t *child_tab, int index, pid_t child, int *end, int *prev_fd)
{
	int i;
	
	if (exec->pipe_to == NULL)
	{
		i = 0;
		while (child_tab[i])
		{
			waitpid(child_tab[i++], NULL, 0);
		}
		waitpid(child, NULL, 0);
		free(child_tab);
	}
	else
	{
		close(end[1]);
		*prev_fd = end[0];
		child_tab[index] = child;
		close(end[1]);
	}
	return (1);
}

// MAIN MANAGEMENT OF THE CHILD EXEC PROCESS (CREATTION OF CHILD, PIPE, PROCESS REDIRECTION)
int	middle_proc(t_exec *exec, pid_t *child_tab, int index, char **envp,
		int *prev_fd)
{
	int		end[2];
	pid_t	child;

	if (exec->pipe_to)
	{
		if (pipe(end) == -1)
			return (0);
	}
	child = fork();
	if (child < 0)
		return (close(end[0]), close(end[1]), 0);
	else if (child == 0)
	{
		if (*prev_fd != STDIN_FILENO)
		{
			dup2(*prev_fd, STDIN_FILENO);
			close(*prev_fd);
		}
		outfile_management(exec, end);
		if (exec_cmd(envp, exec->cmd) == 0)
			return (close(end[1]), exit(EXIT_FAILURE), 0);
	}
	else
		end_or_pipe(exec, child_tab, index, child, end, prev_fd);
	return (1);
}

// CALCUL DU NOMBRE DE NODE DANS LA LISTE CHAINEE POUR AVOIR LE NOMBRE DE PROCESS À WAIT
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
int	task_init(t_exec *exec, int *prev_fd)
{
	int end[2];
	int fd_infile;

	if(exec->if_here_doc == 1)
	{
		if(pipe(end) == -1)
			return (0);
		loop_here_doc(exec->delimiter, end);
		close(end[1]);
		*prev_fd = end[0];	
	}
	if (exec->if_infile == 1)
	{
		fd_infile = open((exec->infile), O_RDONLY);
		if (fd_infile == -1)
			return (0);
		close(end[0]);
		*prev_fd = fd_infile;
	}
	return (1);
}

// GESTION DE LA BOUCLE DE TOUTES LES EXECS À FAIRE ET INIT TU TABLEAU DE CHILD À WAIT
int	pipex(t_exec **lst_exec, char **envp)
{
	t_exec	*tmp;
	pid_t	*child_tab;
	int		index;
	int		prev_fd;

	prev_fd = STDIN_FILENO;
	child_tab = ft_calloc(node_number(*lst_exec) + 1, sizeof(pid_t));
	if (!child_tab)
		return (-1);
	index = 0;
	tmp = *lst_exec;
	while (tmp)
	{
		task_init(tmp, &prev_fd);
		if (middle_proc(tmp, child_tab, index++, envp, &prev_fd) == 0)
			return (-1);
		tmp = tmp->pipe_to;
	}
	return (1);
}
