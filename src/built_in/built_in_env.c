/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:21:47 by pandemonium       #+#    #+#             */
/*   Updated: 2025/06/26 18:10:53 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    exec_unset(t_shell *shell, int i)
{
    char **split;

    while (shell->exec->cmd[i + 1])
    {
        split = ft_split(shell->exec->cmd[i + 1], '=');
        if (ft_get_env(shell->env, split[0]))
            shell->env = unset_env(shell->exec->cmd[i + 1], shell->env);
        if (ft_get_env(shell->secret, split[0]))
           shell->secret = unset_env(shell->exec->cmd[i + 1], shell->secret);
        i++;
    }
}
void stock_export(t_shell *shell, int i)
{
    char **split;

    if (ft_strchr(shell->exec->cmd[i + 1], '='))
    {
        split = ft_split(shell->exec->cmd[i + 1], '=');
        if (ft_get_env(shell->env, split[0]))
            shell->env = set_env(shell, i, split[0], shell->env);
        if (ft_get_env(shell->secret, split[0]))
            shell->secret = set_env(shell, i, split[0], shell->secret);
        if (!ft_get_env(shell->secret, split[0]) && !ft_get_env(shell->env, split[0]))
        {
            shell->env = put_env(shell, i, shell->env);
            shell->secret = put_env(shell, i, shell->secret);
        }
        ft_free_tab((void **)split);
    }
    else
    {
        if (ft_get_env(shell->secret, shell->exec->cmd[i + 1]))
            shell->secret = set_env(shell, i, shell->exec->cmd[i + 1], shell->secret);
        else
            shell->secret = put_env(shell, i, shell->secret);
    }
}

void    exec_export(t_shell	*shell, int i)
{
    int j;
    char **split;

    j = 0;
    if (!shell->exec->cmd[i + 1])
    {
        while (shell->secret[j])
        {
            split = ft_split(shell->secret[j], '=');
            if (ft_strchr(shell->secret[j], '=') == 0)
            {
                if (!ft_get_env(shell->env, split[0]) && !is_valid_env(split[0]))
                    shell->env = put_env(shell, i, shell->env);
                printf("declare -x %s\n", split[0]);
            }
            else
                printf("declare -x %s=\"%s\"\n", split[0], ft_strchr(shell->secret[j], '=') + 1);
            ft_free_tab((void **)split);
            j++;
        }
    }
    else
    {
        while (shell->exec->cmd[i + 1])
        {
            if (!is_valid_env(shell->exec->cmd[i + 1]))
                printf("INVALID ENV: %s\n",shell->exec->cmd[i + 1]);
            else
                stock_export(shell, i);
            i++;
        }
    }
 }

void    check_env(t_shell *shell, int i)
{
    char **split;

    split = ft_split(shell->exec->cmd[i + 1], '=');
    if (!split)
        return ;
    if (ft_get_env(shell->env, split[0]) == 1)
    {
        shell->env = set_env(shell, i, split[0], shell->env);
        ft_free_tab((void **)split);
        return ;
    }
    shell->env = put_env(shell, i, shell->env);
    ft_free_tab((void **)split);
}
void exec_env(t_shell *shell, int i)
{
    int j;

    while (shell->exec->cmd[i + 1])
    {
        if (ft_strchr(shell->exec->cmd[i + 1], '='))
                check_env(shell, i);
        else
            break;
        i++;
    }
    j = 0;
    while (shell->env[j])
    {
        printf("%s\n", shell->env[j]);
        j++;
    }
    i++;
}