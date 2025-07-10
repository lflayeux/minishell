/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:34:39 by alex              #+#    #+#             */
/*   Updated: 2025/07/10 23:42:21 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pipe_outfile(t_shell *shell, t_exec *exec, int *fd_outfile)
{
	if (exec->if_outfile == TRUE)
		*fd_outfile = open((exec->outfile), O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else
		*fd_outfile = open((exec->outfile), O_WRONLY | O_CREAT | O_APPEND,
				0666);
	if (*fd_outfile == ERROR)
		return (print_error(exec->outfile, FILE_MESS, shell, N_FOUND), FALSE);
	if (dup2(*fd_outfile, STDOUT_FILENO) == ERROR)
		return (FALSE);
	return (TRUE);
}

//  MANAGEMENT DE L'OUTFILE/APPEND DANS UN CHILD SI PRESENT SINON PIPE
int	outfile_management(t_exec *exec, int *end, t_shell *shell)
{
	int	fd_outfile;

	fd_outfile = TRUE;
	if (exec->if_outfile == TRUE || exec->if_append == TRUE)
	{
		close_fd(shell, 2, 0);
		if (pipe_outfile(shell, exec, &fd_outfile) == FALSE)
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

void	check_status(int status)
{
	int	sig;

	if (WIFEXITED(status))
		signal_global = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		else if (sig == SIGINT)
			write(STDERR_FILENO, "\n", 1);
		signal_global = 128 + sig;
	}
	else
		signal_global = 0;
}

void	next_pipe(t_shell *shell, pid_t child, int *end)
{
	close_fd(shell, 1, 0);
	if (PIPEX->prev_fd != NONE)
		close(PIPEX->prev_fd);
	PIPEX->prev_fd = end[0];
	PIPEX->child_tab[PIPEX->child_index] = child;
}

//  MANAGEMENT IN PARENT PROCESS IF END OF EXEC STRUCT OR NEXT PIPE
int	end_or_pipe(t_exec *exec, pid_t child, int *end, t_shell *shell)
{
	int	i;
	int	status;

	if (exec->pipe_to == NULL)
	{
		i = 0;
		if (PIPEX->prev_fd != NONE)
			close(PIPEX->prev_fd);
		while (PIPEX->child_tab[i])
		{
			if (waitpid(PIPEX->child_tab[i++], &status, 0) == -1)
				return (FALSE);
			check_status(status);
		}
		if (waitpid(child, &status, 0) == -1)
			return (FALSE);
		check_status(status);
	}
	else
		next_pipe(shell, child, end);
	return (TRUE);
}

int	child_exec(t_shell *shell, t_exec *exec)
{
	child_signals(shell->signals);
	if (PIPEX->prev_fd != NONE && PIPEX->prev_fd != STDIN_FILENO)
	{
		if (dup2(PIPEX->prev_fd, STDIN_FILENO) == -1)
			return (FALSE);
		close(PIPEX->prev_fd);
	}
	outfile_management(exec, PIPEX->end, shell);
	if (!exec->cmd || !exec->cmd[0] || (ft_strcmp((exec->cmd)[0], " ") == 0))
	{
		close_fd(shell, 2, 0);
		free_all(shell);
		exit(0);
	}
	built_in(exec, shell, 0);
	exec_cmd(exec->cmd, shell);
	exit(130);
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
		return (close_fd(shell, 2, 0), FALSE);
	else if (child == 0)
	{
		if (child_exec(shell, exec) == FALSE)
			return (FALSE);
		// child_signals(shell->signals);
		// if (PIPEX->prev_fd != NONE && PIPEX->prev_fd != STDIN_FILENO)
		// {
		// 	if (dup2(PIPEX->prev_fd, STDIN_FILENO) == -1)
		// 		return (FALSE);
		// 	close(PIPEX->prev_fd);
		// }
		// outfile_management(exec, PIPEX->end, shell);
		// if (!exec->cmd || !exec->cmd[0] || (ft_strcmp((exec->cmd)[0],
		// 			" ") == 0))
		// {
		// 	close_fd(shell, 2, 0);
		// 	free_all(shell);
		// 	exit(0);
		// }
		// built_in(exec, shell, 0);
		// exec_cmd(exec->cmd, shell);
		// exit(130);
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
		if (PIPEX->prev_fd != NONE)
			close(PIPEX->prev_fd);
		here_doc_pipe(exec, shell);
		PIPEX->prev_fd = PIPEX->end[0];
		close(PIPEX->end[1]);
	}
	if (exec->if_infile == TRUE)
	{
		fd_infile = open((exec->infile), O_RDONLY);
		if (fd_infile == -1)
			return (FALSE);
		if (PIPEX->prev_fd != NONE)
			close(PIPEX->prev_fd);
		PIPEX->prev_fd = fd_infile;
	}
	return (TRUE);
}

void	loop_pipex(t_shell *shell)
{
	t_exec	*tmp;

	tmp = shell->exec;
	while (tmp)
	{
		if (task_init(tmp, shell) == FALSE)
			break ;
		if (tmp->cmd && tmp->cmd[0] && ft_strcmp((tmp->cmd)[0], "") == 0)
		{
			print_error(" ", N_CMD_MESS, shell, N_FOUND);
			tmp = tmp->pipe_to;
			continue ;
		}
		middle_proc(tmp, shell);
		tmp = tmp->pipe_to;
	}
}

// GESTION DE LA BOUCLE DE TOUTES LES EXECS À FAIRE ET INIT TU TABLEAU DE CHILD À WAIT
int	pipex(t_shell *shell)
{
	PIPEX->child_tab = ft_calloc(node_number(shell->exec) + 1, sizeof(pid_t));
	if (!(PIPEX->child_tab))
		return (print_error("malloc", NULL, shell, GEN_ERR), FALSE);
	PIPEX->child_tab[node_number(shell->exec)] = '\0';
	if (shell->exec->pipe_to == NULL && built_in(shell->exec, shell, 1))
		return (TRUE);
	else
		loop_pipex(shell);
	if (PIPEX->child_tab)
		free(PIPEX->child_tab);
	PIPEX->child_tab = NULL;
	return (TRUE);
}
