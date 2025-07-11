/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:34:39 by alex              #+#    #+#             */
/*   Updated: 2025/07/11 19:01:04 by aherlaud         ###   ########.fr       */
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
		if (PIPEX->prev_fd != NONE)
			close(PIPEX->prev_fd);
		while (PIPEX->child_tab[i])
		{
			if (waitpid(PIPEX->child_tab[i++], &status, 0) == -1)
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
	}
	else
	{
		parent_signals(shell->signals);
		end_or_pipe(exec, child, PIPEX->end, shell);
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

// GESTION DE LA BOUCLE DE TOUTES LES EXECS À FAIRE
// ET INIT TU TABLEAU DE CHILD À WAIT
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
