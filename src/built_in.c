/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:33:18 by lflayeux          #+#    #+#             */
/*   Updated: 2025/05/22 18:52:26 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void    exec_pwd(int *i)
{
    char path[1024];
    printf("%s\n", getcwd(path, 1024));
    (*i)++;
}

void    built_in(t_exec	**exec, int *i)
{
    // if (ft_strcmp(exec->cmd, "echo"))
    //     exec_echo(exec, i);
    // else if (ft_strcmp(exec->cmd, "cd"))
    //     exec_cd(exec, i);
    if (ft_strcmp((*exec)->cmd[*i], "pwd"))
        exec_pwd(i);
    else
        return;
}