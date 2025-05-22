/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:34:39 by alex              #+#    #+#             */
/*   Updated: 2025/05/22 20:13:29 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**find_path_env(char **envp)
{
	int		i;
	size_t	len;
	char	*path_str;
	char	**all_paths;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			break ;
		i++;
	}
	len = ft_strlen(envp[i]);
	path_str = ft_substr(envp[i], 5, len - 5);
	if (!path_str)
		return (NULL);
	all_paths = ft_split(path_str, ':');
	return (free(path_str), all_paths);
}

int	handle_path_cmd(char **cmd_parsed, char **envp)
{
	if (access(cmd_parsed[0], X_OK) == 0)
	{
		if (execve(cmd_parsed[0], cmd_parsed, envp) == -1)
			return (0);
	}
	else
		return (0);
	return (1);
}

int	exec_proc(char **cmd_parsed, char **all_paths, char **envp, int i)
{
	char	*temp;
	char	*path;

	if (cmd_parsed[0][0] == '/')
	{
		if (handle_path_cmd(cmd_parsed, envp) == 0)
			return (0);
		return (1);
	}
	temp = ft_strjoin("/", cmd_parsed[0]);
	if (!temp)
		return (0);
	path = ft_strjoin(all_paths[i], temp);
	if (!path)
		return (0);
	if (access(path, X_OK) == 0)
	{
		if (execve(path, cmd_parsed, envp) == -1)
			return (0);
	}
	// execve(path, cmd_parsed, envp);
	return (free(temp), free(path), free(all_paths[i]), 1);
}

// int	exec_cmd(char **envp, char **cmd, int *tab_child)
int	exec_cmd(char **envp, char **cmd)
{
	// char	**cmd_parsed;
	char	**all_paths;
	int		i;

	// if (ft_is_empty(cmd) == 1)
	// 	return (free(tab_child), errno = ENOENT, perror(" "), exit(1), 0);
	// cmd_parsed = ft_split_dif(cmd, ' ');
	// if (!cmd_parsed)
	// 	return (0);
	all_paths = find_path_env(envp);
	if (!all_paths)
		return (free(cmd), 0);
	i = 0;
	while (all_paths[i] != NULL)
	{
		if (exec_proc(cmd, all_paths, envp, i) == 0)
			return (exit(1), 0);
			// return (free(tab_child), free_tab(all_paths), perror(cmd[0]),
			// 	free_tab(cmd), exit(1), 0);
		i++;
	}
	// return (free(tab_child), free(all_paths), perror(cmd[0]),
	// 	free_tab(cmd), exit(1), 0);
	return (exit(1), 0);
}
