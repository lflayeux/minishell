/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:21:47 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/09 23:30:24 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    exec_unset(t_shell *shell, int i, t_exec *exec)
{
    char **split;

    while (exec->cmd[i + 1])
    {
        split = ft_split(exec->cmd[i + 1], '=');
        if (ft_get_env(shell->env, split[0]))
            shell->env = unset_env(shell->exec->cmd[i + 1], shell->env);
        if (ft_get_env(shell->secret, split[0]))
           shell->secret = unset_env(exec->cmd[i + 1], shell->secret);
        ft_free_tab((void **)split);
        i++;
    }
}
void stock_export(t_shell *shell, int i, char *cmd)
{
    char **split;

    if (ft_strchr(cmd, '='))
    {
        split = ft_split(cmd, '=');
        if (ft_get_env(shell->env, split[0]))
            shell->env = set_env(shell, i, split[0], shell->env);
        if (ft_get_env(shell->secret, split[0]))
            shell->secret = set_env(shell, i, split[0], shell->secret);
        if (!ft_get_env(shell->env, split[0]) && ft_get_env(shell->secret, split[0]))
            shell->env = put_env(shell, shell->env, cmd);
        if (!ft_get_env(shell->secret, split[0]) && !ft_get_env(shell->env, split[0]))
        {
            shell->env = put_env(shell, shell->env, cmd);
            shell->secret = put_env(shell, shell->secret, cmd);
        }
        ft_free_tab((void **)split);
    }
    else
    {
        if (ft_get_env(shell->secret, cmd))
            shell->secret = set_env(shell, i, cmd, shell->secret);
        else
            shell->secret = put_env(shell, shell->secret, cmd);
    }
}

void    exec_export(t_shell	*shell, int i, t_exec *exec)
{
    int j;
    char **split;

    j = 0;
    if (!exec->cmd[1] || ft_strcmp(exec->cmd[1], " ") == 0)
    {
        while (shell->secret[j])
        {
            split = ft_split(shell->secret[j], '=');
            if (ft_strchr(shell->secret[j], '=') == 0)
            {
                if (!ft_get_env(shell->env, split[0]) && !is_valid_env(split[0]))
                    shell->env = put_env(shell, shell->env, exec->cmd[i + 1]);
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
        i++;
        while (exec->cmd[i])
        {
            if (!is_valid_env(exec->cmd[i]))
                print_error(exec->cmd[i], "not a valid identifier", shell, GEN_ERROR);
            else
                stock_export(shell, i, exec->cmd[i]);
            i++;
        }
    }
 }						

void    check_env(t_shell *shell, int i, char *cmd)
{
    char **split;

    split = ft_split(cmd, '=');
    if (!split)
        return ;
    if (ft_get_env(shell->env, split[0]) == 1)
    {
        shell->env = set_env(shell, i, split[0], shell->env);
        ft_free_tab((void **)split);
        return ;
    }
    shell->env = put_env(shell, shell->env, cmd);
    ft_free_tab((void **)split);
}
void exec_env(t_shell *shell, int i, t_exec *exec)
{
    int j;

    while (exec->cmd[i])
    {
        if (ft_strchr(exec->cmd[i], '='))
                check_env(shell, i, exec->cmd[i]);
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