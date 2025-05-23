/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:33:18 by lflayeux          #+#    #+#             */
/*   Updated: 2025/05/23 17:39:30 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    exec_pwd()
{
    char *path;
    path = getcwd(NULL, 0);
    printf(YLW"%s\n"RST, path);
    free(path);
}

void    exec_cd(char *path)
{
    chdir(path);
    exec_pwd();
}

void exec_echo(t_exec **exec, int *i)
{
    int newline;
    int j;

    (*i)++;
    newline = 1;
    while ((*exec)->cmd[*i])
    {
        if (ft_strncmp((*exec)->cmd[*i], "-n", 2) == 0)
        {
            j = 2;
            while ((*exec)->cmd[*i][j] == 'n')
                j++;
            if ((*exec)->cmd[*i][j] == '\0')
            {
                newline = 0;
                (*i)++;
                continue;
            }
        }
        break;
    }
    while ((*exec)->cmd[*i])
    {
        printf("%s", (*exec)->cmd[*i]);
        if ((*exec)->cmd[*i + 1])
            printf(" ");
        (*i)++;
    }
    if (newline)
        printf("\n");
}
void    exec_env(t_exec	**exec, int *i, char **env)
{
    char    **new_env;
    char    **search_env;
    int     j;

    j = 0;
    while ((*exec)->cmd[*i + 1])
    {
        search_env = ft_split((*exec)->cmd[*i + 1], '=');
        if (!search_env[1])
            printf("ERROR");
        else
        {
            while ()


        }
    }
    
}

void    built_in(t_exec	**exec, int *i, char **env)
{
    if (!(ft_strcmp((*exec)->cmd[*i], "echo")))
        exec_echo(exec, i);
    else if (ft_strcmp((*exec)->cmd[*i], "cd") == 0)
         exec_cd((*exec)->cmd[++(*i)]);
    else if (ft_strcmp((*exec)->cmd[*i], "pwd") == 0)
        exec_pwd();
    else if (ft_strcmp((*exec)->cmd[*i], "env") == 0)
        exec_env(exec, i, env);
    else
        return;
}