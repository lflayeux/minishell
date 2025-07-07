/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:33:18 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/07 18:50:09 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// ==================
// ======= PWD ======
// ==================

void	exec_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return ;
	printf(YLW "%s\n" RST, path);
	free(path);
}
// ==================
// ======= CD =======
// ==================

void	exec_cd(char **path, int i, t_shell *shell)
{
	char	*direction;

	direction = NULL;
	if (path[i + 1] && path[i + 2])
	{
		signal_global = GEN_ERROR;
		printf("minishell: cd: too many arguments\n");
		free_all(shell);
		exit(1);
	}
	else if (path[i + 1] == NULL)
		direction = ft_strdup(getenv("HOME"));
	else if (path[i + 1][0] == '~')
		direction = ft_strjoin(getenv("HOME"), &path[i + 1][1]);
	else
		direction = ft_strdup(path[i + 1]);
	if (chdir(direction) == -1)
		print_error("cd", path[i + 1], shell, GEN_ERROR);
	if (direction)
		free(direction);
	exec_pwd();
}
// ==================
// ======= ECHO =====
// ==================

void	exec_echo(t_exec *exec, int i)
{
	int	newline;
	int	j;

	i++;
	newline = 1;
	while (exec->cmd[i])
	{
		if (ft_strncmp(exec->cmd[i], "-n", 2) == 0)
		{
			j = 2;
			while (exec->cmd[i][j] == 'n')
				j++;
			if (exec->cmd[i][j] == '\0')
			{
				newline = 0;
				i++;
				continue ;
			}
		}
		break ;
	}
	while (exec->cmd[i])
	{
		printf("%s", exec->cmd[i]);
		if (exec->cmd[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}

int	built_in(t_exec *exec, t_shell *shell)
{
	if (!exec->cmd || exec->cmd[0] == NULL)
		return (FALSE);
	if (!(ft_strcmp(exec->cmd[0], "echo")))
		exec_echo(exec, PIPEX->i);
	else if (ft_strcmp(exec->cmd[0], "cd") == 0)
		exec_cd(exec->cmd, PIPEX->i, shell);
	else if (ft_strcmp(exec->cmd[0], "pwd") == 0)
		exec_pwd();
	else if (ft_strcmp(exec->cmd[0], "env") == 0)
		exec_env(shell, PIPEX->i);
	else if (ft_strcmp(exec->cmd[0], "export") == 0)
		exec_export(shell, PIPEX->i);
	else if (ft_strcmp(exec->cmd[0], "unset") == 0)
		exec_unset(shell, PIPEX->i);
	else
		return (FALSE);
	free_all(shell);
	exit(0);
	return (TRUE);
}
