/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:33:18 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/01 14:51:48 by lflayeux         ###   ########.fr       */
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

void	exec_cd(char **path, int i)
{
	char	*join;

	if (path[i + 1] == NULL)
	{
		join = ft_strdup(getenv("HOME"));
		printf("%s\n", join);
		chdir(join);
		free(join);
	}
	else if (path[i][0] == '~')
	{
		join = ft_strjoin(getenv("HOME"), path[i] + 1);
		printf("%s\n", join);
		chdir(join);
	}
	else
		chdir(path[i]);
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
		exec_echo(exec, 0);
	else if (ft_strcmp(exec->cmd[0], "cd") == 0)
		exec_cd(exec->cmd, 0);
	else if (ft_strcmp(exec->cmd[0], "pwd") == 0)
		exec_pwd();
	else if (ft_strcmp(exec->cmd[0], "env") == 0)
		exec_env(shell, 0);
	else if (ft_strcmp(exec->cmd[0], "export") == 0)
		exec_export(shell, 0);
	else if (ft_strcmp(exec->cmd[0], "unset") == 0)
		exec_unset(shell, 0);
	else
	{
		return (FALSE);
	}
	return (TRUE);
}
