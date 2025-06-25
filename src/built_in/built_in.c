/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:33:18 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/25 18:58:45 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// ==================
// ======= PWD ======
// ==================

void    exec_pwd()
{
    char *path;
    path = getcwd(NULL, 0);
	if (path == NULL)
		
    printf(YLW"%s\n"RST, path);
    free(path);
}
// ==================
// ======= CD =======
// ==================

void    exec_cd(char *path)
{
    char    *join;

    if (path[0] == '~')
    {
        join = ft_strjoin(getenv("HOME"), path + 1);
        printf("%s\n", join);
        chdir(join);
    }
    else
        chdir(path);
    exec_pwd();
}
// ==================
// ======= ECHO =====
// ==================

void exec_echo(t_exec *exec, int *i)
{
    int newline;
    int j;

    (*i)++;
    newline = 1;
    while (exec->cmd[*i])
    {
        if (ft_strncmp(exec->cmd[*i], "-n", 2) == 0)
        {
            j = 2;
            while (exec->cmd[*i][j] == 'n')
                j++;
            if (exec->cmd[*i][j] == '\0')
            {
                newline = 0;
                (*i)++;
                continue;
            }
        }
        break;
    }
    while (exec->cmd[*i])
    {
        printf("%s", exec->cmd[*i]);
        if (exec->cmd[*i + 1])
            printf(" ");
        (*i)++;
    }
    if (newline)
        printf("\n");
}

void    built_in(t_shell *shell, int *i)
{
    if (!(ft_strcmp(shell->exec->cmd[*i], "echo")))
        exec_echo(shell->exec, i);
    else if (ft_strcmp(shell->exec->cmd[*i], "cd") == 0)
        exec_cd(shell->exec->cmd[++(*i)]);
    else if (ft_strcmp(shell->exec->cmd[*i], "pwd") == 0)
        exec_pwd();
    else if (ft_strcmp(shell->exec->cmd[*i], "env") == 0)
        exec_env(shell i);
    else if (ft_strcmp(shell->exec->cmd[*i], "export") == 0)
        exec_export(shell i);
   else if (ft_strcmp(shell->exec->cmd[*i], "unset") == 0)
		exec_unset(shell, i);
    else
        return ;
}
