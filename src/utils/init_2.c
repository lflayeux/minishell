/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:31:53 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/11 00:33:30 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exec_init(t_exec *node_exec)
{
	node_exec->cmd = NULL;
	node_exec->infile = NULL;
	node_exec->outfile = NULL;
	node_exec->here_doc = NULL;
	node_exec->if_infile = 0;
	node_exec->if_outfile = 0;
	node_exec->if_append = 0;
	node_exec->if_here_doc = 0;
	node_exec->pipe_to = NULL;
}
void	get_pid(t_shell *shell)
{
	int		fd;
	char	*line;
	char	**split;
	char	*tmp;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd == -1)
		print_error("malloc", NULL, shell, GEN_ERR);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "Pid:", 4) == 0)
		{
			split = ft_split(line, '\t');
			if (!split)
				print_error("malloc", NULL, shell, GEN_ERR);
			tmp = ft_substr(split[1], 0, ft_strlen(split[1]) - 1);
			shell->pid = tmp;
			ft_free_tab((void **)split);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
void	init_fd(t_shell *shell)
{
	PIPEX->end[0] = NONE;
	PIPEX->end[1] = NONE;
}
void	init_pipex(t_shell *shell)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (print_error("malloc", NULL, shell, GEN_ERR));
	PIPEX = pipex;
	PIPEX->child_tab = NULL;
	PIPEX->child_index = 0;
	PIPEX->prev_fd = NONE;
	init_fd(shell);
}