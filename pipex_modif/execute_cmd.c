/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:34:39 by alex              #+#    #+#             */
/*   Updated: 2025/06/02 17:51:47 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// malloc ok
char	**find_path_env(t_shell *shell)
{
	int		i;
	size_t	len;
	char	*path_str;
	char	**all_paths;

	i = 0;
	while (shell->env[i] != NULL)
	{
		if (ft_strncmp("PATH=", shell->env[i], 5) == 0)
			break ;
		i++;
	}
	len = ft_strlen(shell->env[i]);
	path_str = ft_substr(shell->env[i], 5, len - 5);
	add_or_free(shell, path_str, NULL, 0);
	all_paths = ft_split(path_str, ':');
	add_or_free(shell, NULL, all_paths, 1);
	return (all_paths);
}

// malloc ok
int	handle_path_cmd(char **cmd_parsed, char *path, t_shell *shell)
{
	if (access(path, X_OK) == 0)
	{
		printf("ici je vais ");
		if (execve(path, cmd_parsed, shell->env) == -1)
			free_exit(shell);
	}
	// else
	// 	return (exit(1), 0);
	return (1);
}

// malloc ok
int	exec_proc(char **cmd_parsed, char **all_paths, t_shell *shell, int i)
{
	char	*temp;
	char	*path;

	if (cmd_parsed[0][0] == '/')
	{
		handle_path_cmd(cmd_parsed, cmd_parsed[0], shell);
		// if (handle_path_cmd(cmd_parsed, cmd_parsed[0], shell) == 0)
		// 	return (0);
		return (1);
	}
	temp = ft_strjoin("/", cmd_parsed[0]);
	add_or_free(shell, temp, NULL, 0);
	path = ft_strjoin(all_paths[i], temp);
	add_or_free(shell, path, NULL, 0);
	// if (access(path, X_OK) == 0)
	// {
	// 	if (execve(path, cmd_parsed, shell->env) == -1)
	// 		return (exit(1), 0);
	// }
	handle_path_cmd(cmd_parsed, path, shell);
	// execve(path, cmd_parsed, shell->env);
	return (1);
}

// int	exec_cmd(char **envp, char **cmd, int *tab_child)
// malloc ok
int	exec_cmd(char **cmd, t_shell *shell)
{
	char	**all_paths;
	int		i;

	all_paths = find_path_env(shell);
	i = 0;
	while (all_paths[i] != NULL)
	{
		exec_proc(cmd, all_paths, shell, i);
		i++;
	}
	return (exit(1), 0);
}
