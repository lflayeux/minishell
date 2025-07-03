/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:34:39 by alex              #+#    #+#             */
/*   Updated: 2025/07/04 01:39:28 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	if (!path_str)
		print_error("malloc", NULL, shell, GEN_ERROR);
	all_paths = ft_split(path_str, ':');
	if (!all_paths)
		print_error("malloc", NULL, shell, GEN_ERROR);
	free(path_str);
	return (all_paths);
}

int is_slash(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '/')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int    handle_path_cmd(char **cmd_parsed, char *path, t_shell *shell)
{
	struct stat    st;

	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			print_error(path, "Is a directory", shell, CMD_EXEC);
			exit(CMD_EXEC);
		}
	}
	if (access(path, F_OK) == -1 && is_slash(cmd_parsed[0]))
	{
		print_error(path, "No such file or directory", shell, N_FOUND);
		exit(N_FOUND);
	}
    if (access(path, X_OK) == 0)
    {
        if (execve(path, cmd_parsed, shell->env) == -1)
            print_error(cmd_parsed[0], NULL, shell, CMD_EXEC);
    }
    return (TRUE);
}

// malloc ok
int	exec_proc(char **cmd_parsed, char **all_paths, t_shell *shell, int i)
{
	char	*temp;
	char	*path;

	handle_path_cmd(cmd_parsed, cmd_parsed[0], shell);
	temp = ft_strjoin("/", cmd_parsed[0]);
	if (!temp)
		return (FALSE);
	path = ft_strjoin(all_paths[i], temp);
	if (!path)
		return (free(temp), FALSE);
	handle_path_cmd(cmd_parsed, path, shell);
	free(path);
	free(temp);
	return (TRUE);
}

// int	exec_cmd(char **envp, char **cmd, int *tab_child)
// malloc ok
int	exec_cmd(char **cmd, t_shell *shell)
{
	char	**all_paths;
	int		i;

	if (!cmd)
		return (FALSE);
	all_paths = find_path_env(shell);
	i = 0;
	while (all_paths[i] != NULL)
	{
		if (exec_proc(cmd, all_paths, shell, i) == FALSE)
			return (FALSE);
		i++;
	}
	print_error(cmd[0], N_CMD_MESS, shell, 0);
	free_all(shell);
	ft_free_tab((void **)all_paths);
	return (exit(127), FALSE);
}
