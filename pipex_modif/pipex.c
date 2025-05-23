/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:34:39 by alex              #+#    #+#             */
/*   Updated: 2025/05/23 15:30:37 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	last_proc(char **envp, char *cmd, int fd_outfile, pid_t *tab_child)
// {
// 	pid_t	child;
// 	int		i;

// 	child = fork();
// 	if (child < 0)
// 		return (0);
// 	else if (child == 0)
// 	{
// 		dup2(fd_outfile, STDOUT_FILENO);
// 		close(fd_outfile);
// 		if (exec_cmd(envp, cmd, tab_child) == 0)
// 			return (free(tab_child), exit(EXIT_FAILURE), 0);
// 	}
// 	else
// 	{
// 		i = 0;
// 		while (tab_child[i])
// 			waitpid(tab_child[i++], NULL, 0);
// 		waitpid(child, NULL, 0);
// 		free(tab_child);
// 		close(fd_outfile);
// 	}
// 	return (1);
// }

// int	task_init(char **av, int *fd_infile)
// {
// 	*fd_infile = open(av[1], O_RDONLY);
// 	if (*fd_infile == -1)
// 		perror("Error infile");
// 	else
// 	{
// 		dup2(*fd_infile, 0);
// 		close(*fd_infile);
// 	}
// 	return (2);
// }

// int	space_proc(t_exec *exec, int *end)
// {
// 	(void)exec;
// 	// if (data->fd_infile == -1 && index == 0)
// 	// 	return (free(data->child_tab), close(end[1]), close(end[0]), exit(1));
// 	close(end[0]);
// 	dup2(end[1], 1);
// 	close(end[1]);
// 	return (1);
// }

int	middle_proc(t_exec *exec, pid_t *child_tab, int index, char **envp,
		int *prev_fd)
{
	int		end[2];
	pid_t	child;
	int		fd_outfile;
	int		i;

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
		if (exec->pipe_to == NULL)
		{
			// printf("\t\t\t\t\t\t\t\tTEST\n");
			// close(end[1]);
			// close(end[0]);
			if (exec->if_outfile == 1)
			{
				fd_outfile = open((exec->outfile), O_WRONLY | O_TRUNC | O_CREAT,
						0666);
				if (fd_outfile == -1)
					return (0);
				dup2(fd_outfile, STDOUT_FILENO);
				close(fd_outfile);
			}
		}
		else
		{
			close(end[0]);
			dup2(end[1], 1);
			close(end[1]);
		}
		if (exec_cmd(envp, exec->cmd) == 0)
			return (close(end[1]), exit(EXIT_FAILURE), 0);
	}
	else
	{
		if (exec->pipe_to == NULL)
		{
			i = 0;
			while (child_tab[i])
			{
				waitpid(child_tab[i++], NULL, 0);
			}
			waitpid(child, NULL, 0);
			// while (wait(NULL) > 0)
			// {
			// }
			free(child_tab);
			// close(fd_outfile);
		}
		else
		{
			close(end[1]);
			/* Keep the read end around to feed into the next child */
			*prev_fd = end[0];
			child_tab[index] = child;
			close(end[1]);
		}
	}
	return (1);
}

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

int	pipex(t_exec **lst_exec, char **envp)
{
	t_exec	*tmp;
	pid_t	*child_tab;
	int		index;
	int		prev_fd;
	int		fd_infile;

	prev_fd = STDIN_FILENO;
	child_tab = ft_calloc(node_number(*lst_exec) + 1, sizeof(pid_t));
	if (!child_tab)
		return (-1);
	// data->fd_infile = 0;
	// i = task_init(data->av, &(data->fd_infile));
	// if (i == -1)
	// 	return (free(data->child_tab), -1);
	index = 0;
	tmp = *lst_exec;
	while (tmp)
	{
		if (tmp->if_infile == 1)
		{
			fd_infile = open((tmp->infile), O_RDONLY);
			if (fd_infile == -1)
				return (0);
			prev_fd = fd_infile;
		}
		if (middle_proc(tmp, child_tab, index++, envp, &prev_fd) == 0)
			return (-1);
		tmp = tmp->pipe_to;
	}
	// data->fd_outfile = open(data->av[data->ac - 1],
	// 		O_WRONLY | O_TRUNC | O_CREAT, 0666);
	// if (last_proc(data->envp, data->av[i], data->fd_outfile,
	// 		data->child_tab) == 0)
	// return (close(data->fd_outfile), -1);
	return (1);
}

// int	main(int ac, char **av, char **envp)
// {
// 	t_pipex	data;
// 	int		i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
// 			break ;
// 		i++;
// 	}
// 	if (!(envp[i]))
// 		return (ft_printf("Error : Can't find or access PATH variable\n"));
// 	if (ac != 5)
// 		return (ft_printf("error on the number of arguments given\n"));
// 	data.ac = ac;
// 	data.av = av;
// 	data.envp = envp;
// 	if ((pipex(&data)) == -1)
// 		return (ft_printf("Error : Pipex function failed to be complete\n"));
// 	return (0);
// }
