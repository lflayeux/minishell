/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:55:50 by alex              #+#    #+#             */
/*   Updated: 2025/05/19 15:24:52 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	**av;
	int		ac;
	char	**envp;
	pid_t	*child_tab;
	int		fd_infile;
	int		fd_outfile;
}			t_pipex;

char		**ft_split_dif(char const *s, char c);

int			here_doc_proc(char *delimiter);

int			exec_cmd(char **envp, char *cmd, int *tab_child);

void		space_proc(t_pipex *data, int index, int *end);

int			ft_is_empty(char *str);

#endif