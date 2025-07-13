/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:14:25 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/13 15:12:02 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pipe_outfile(t_shell *shell, t_exec *exec, int *fd_outfile)
{
	struct stat	st;
	
	if (stat((exec->outfile), &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			return (print_error((exec->outfile), "Is a directory", shell, CMD_EXEC), exit (1),
				FALSE);
	}
	if (exec->if_outfile == TRUE)
		*fd_outfile = open((exec->outfile), O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else
		*fd_outfile = open((exec->outfile), O_WRONLY | O_CREAT | O_APPEND,
				0666);
	if (*fd_outfile == ERROR)
	{
		return (print_error(exec->outfile, PERM, shell, 1), free_all(shell), exit(1), 0);		
	}
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

void check_status(int status, t_shell *shell)
{
	int	sig;

	if (WIFEXITED(status))
	{
		g_signal_global = WEXITSTATUS(status);
		if(g_signal_global == 25)
			free_error(shell);
	}
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		else if (sig == SIGINT)
			write(STDERR_FILENO, "\n", 1);
		g_signal_global = 128 + sig;
	}
	else
		g_signal_global = 0;
}

void	next_pipe(t_shell *shell, pid_t child, int *end)
{
	close_fd(shell, 1, 0);
	if ((shell->pipex)->prev_fd != NONE)
		close((shell->pipex)->prev_fd);
	(shell->pipex)->prev_fd = end[0];
	(shell->pipex)->child_tab[(shell->pipex)->child_index] = child;
}
/**
	CALCUL DU NOMBRE DE NODE DANS LA LISTE CHAINEE
	POUR AVOIR LE NOMBRE DE PROCESS À WAIT

	@param lst_exec La liste chaine sur laquelle on compte

	@return			Le nombre de node dans la liste chainee. 0 si pas de liste chainee

*/
int	node_number(t_exec *lst_exec)
{
	t_exec *tmp;
	int len;

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