/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:34:39 by alex              #+#    #+#             */
/*   Updated: 2025/07/13 16:38:54 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//  MANAGEMENT IN PARENT PROCESS IF END OF EXEC STRUCT OR NEXT PIPE
int	end_or_pipe(t_exec *exec, pid_t child, int *end, t_shell *shell)
{
	int	i;
	int	status;

	if (exec->pipe_to == NULL)
	{
		i = 0;
		if ((shell->pipex)->prev_fd != NONE)
			close((shell->pipex)->prev_fd);
		while ((shell->pipex)->child_tab[i])
		{
			if (waitpid((shell->pipex)->child_tab[i++], &status, 0) == -1)
				return (FALSE);
			check_status(status, shell);
		}
		if (waitpid(child, &status, 0) == -1)
			return (FALSE);
		check_status(status, shell);
	}
	else
		next_pipe(shell, child, end);
	return (TRUE);
}

int	child_exec(t_shell *shell, t_exec *exec)
{
	child_signals(shell->signals);
	if ((shell->pipex)->prev_fd != NONE && (shell->pipex)->prev_fd != STDIN_FILENO)
	{
		if (dup2((shell->pipex)->prev_fd, STDIN_FILENO) == -1)
			return (FALSE);
		close((shell->pipex)->prev_fd);
	}
	outfile_management(exec, (shell->pipex)->end, shell);
	if (!exec->cmd || !exec->cmd[0] || (ft_strcmp((exec->cmd)[0], " ") == 0))
	{
		close_fd(shell, 2, 0);
		free_all(shell);
		exit(0);
	}
	signal(SIGPIPE, SIG_IGN);
	built_in(exec, shell, 0);
	signal(SIGPIPE, SIG_DFL);
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
		if (pipe((shell->pipex)->end) == -1)
			return (FALSE);
	}
	child = fork();
	if (child < 0)
		return (close_fd(shell, 2, 0), FALSE);
	else if (child == 0)
	{
		if(exec->if_infile == TRUE && access(exec->infile, R_OK) == - 1)
		 	return (close((shell->pipex)->prev_fd), free_all(shell), exit(1), FALSE);
		if (child_exec(shell, exec) == FALSE)
			return (FALSE);
	}
	else
	{
		parent_signals(shell->signals);
		end_or_pipe(exec, child, (shell->pipex)->end, shell);
	}
	return (TRUE);
}

void	loop_pipex(t_shell *shell)
{
	t_exec	*tmp;

	tmp = shell->exec;
	while (tmp)
	{
		// if (task_init(tmp, shell) == FALSE)
		// {
		// 	tmp = tmp->pipe_to;
		// 	continue ;
		// }
		task_init(tmp, shell);
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

// GESTION DE LA BOUCLE DE TOUTES LES EXECS À FAIRE
// ET INIT TU TABLEAU DE CHILD À WAIT
int	pipex(t_shell *shell)
{
	(shell->pipex)->child_tab = ft_calloc(node_number(shell->exec) + 1, sizeof(pid_t));
	if (!((shell->pipex)->child_tab))
		return (free_error(shell), FALSE);
	(shell->pipex)->child_tab[node_number(shell->exec)] = '\0';
	if (shell->exec->pipe_to == NULL && built_in(shell->exec, shell, 1))
		return (TRUE);
	else
		loop_pipex(shell);
	if ((shell->pipex)->child_tab)
		free((shell->pipex)->child_tab);
	(shell->pipex)->child_tab = NULL;
	return (TRUE);
}
