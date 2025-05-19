/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:34:39 by alex              #+#    #+#             */
/*   Updated: 2025/05/19 15:27:39 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	middle_proc(t_pipex *data, char *cmd, int index)
{
	int		end[2];
	pid_t	child;

	if (pipe(end) == -1)
		return (0);
	child = fork();
	if (child < 0)
		return (close(end[0]), close(end[1]), 0);
	else if (child == 0)
	{
		space_proc(data, index, end);
		if (exec_cmd(data->envp, cmd, data->child_tab) == 0)
			return (free(data->child_tab), close(end[1]), exit(EXIT_FAILURE),
				0);
	}
	else
	{
		data->child_tab[index] = child;
		close(end[1]);
		if (dup2(end[0], 0) == -1)
			return (close(end[0]), 0);
		close(end[0]);
	}
	return (1);
}

int	last_proc(char **envp, char *cmd, int fd_outfile, pid_t *tab_child)
{
	pid_t	child;
	int		i;

	child = fork();
	if (child < 0)
		return (0);
	else if (child == 0)
	{
		dup2(fd_outfile, STDOUT_FILENO);
		close(fd_outfile);
		if (exec_cmd(envp, cmd, tab_child) == 0)
			return (free(tab_child), exit(EXIT_FAILURE), 0);
	}
	else
	{
		i = 0;
		while (tab_child[i])
			waitpid(tab_child[i++], NULL, 0);
		waitpid(child, NULL, 0);
		free(tab_child);
		close(fd_outfile);
	}
	return (1);
}

int	task_init(char **av, int *fd_infile)
{
	*fd_infile = open(av[1], O_RDONLY);
	if (*fd_infile == -1)
		perror("Error infile");
	else
	{
		dup2(*fd_infile, 0);
		close(*fd_infile);
	}
	return (2);
}

int	pipex(t_pipex *data)
{
	int	i;
	int	index;

	data->child_tab = ft_calloc(data->ac - 1, sizeof(pid_t));
	if (!(data->child_tab))
		return (-1);
	data->fd_infile = 0;
	i = task_init(data->av, &(data->fd_infile));
	if (i == -1)
		return (free(data->child_tab), -1);
	index = 0;
	while (i < (data->ac - 2))
	{
		if (middle_proc(data, data->av[i++], index++) == 0)
			return (free(data->child_tab), -1);
	}
	data->fd_outfile = open(data->av[data->ac - 1],
			O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (last_proc(data->envp, data->av[i], data->fd_outfile,
			data->child_tab) == 0)
		return (close(data->fd_outfile), -1);
	return (close(data->fd_outfile), 1);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	data;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!(envp[i]))
		return (ft_printf("Error : Can't find or access PATH variable\n"));
	if (ac != 5)
		return (ft_printf("error on the number of arguments given\n"));
	data.ac = ac;
	data.av = av;
	data.envp = envp;
	if ((pipex(&data)) == -1)
		return (ft_printf("Error : Pipex function failed to be complete\n"));
	return (0);
}
