/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:05:17 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/11 00:05:50 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void stock_export(t_shell *shell, char *cmd)
{
    char **split;

    if (ft_strchr(cmd, '='))
    {
        split = ft_split(cmd, '=');
        if (GET_ENV(shell->env, split[0]))
            shell->env = set_env(split[0], shell->env, cmd);
        if (GET_ENV(shell->secret, split[0]))
            shell->secret = set_env(split[0], shell->secret, cmd);
        if (!GET_ENV(shell->env, split[0]) && GET_ENV(shell->secret, split[0]))
            shell->env = put_env(shell, shell->env, cmd);
        if (!GET_ENV(shell->secret, split[0]) && !GET_ENV(shell->env, split[0]))
        {
            shell->env = put_env(shell, shell->env, cmd);
            shell->secret = put_env(shell, shell->secret, cmd);
        }
        ft_free_tab((void **)split);
    }
    else
    {
        if (GET_ENV(shell->secret, cmd))
            shell->secret = set_env(cmd, shell->secret, cmd);
        else
            shell->secret = put_env(shell, shell->secret, cmd);
    }
}

void	export_print(t_shell	*shell, int i, t_exec *exec)
{
	int j;
    char **split;

    j = 0;
    while (shell->secret[j])
    {
        split = ft_split(shell->secret[j], '=');
        if (ft_strchr(shell->secret[j], '=') == 0)
        {
            if (!GET_ENV(shell->env, split[0]) && !is_valid_env(split[0]))
                shell->env = put_env(shell, shell->env, exec->cmd[i + 1]);
            printf("declare -x %s\n", split[0]);
        }
        else
            printf("declare -x %s=\"%s\"\n", split[0], \
				ft_strchr(shell->secret[j], '=') + 1);
        ft_free_tab((void **)split);
        j++;
    }
}


int   exec_export(t_shell	*shell, int i, t_exec *exec)
{
    if (!exec->cmd[1] || ft_strcmp(exec->cmd[1], " ") == 0)
		export_print(shell, i, exec);
    else
    {
        i++;
        while (exec->cmd[i])
        {
            if (!is_valid_env(exec->cmd[i]))
                return(print_error(exec->cmd[i], ID, shell, 1), 1);
            else
                stock_export(shell, exec->cmd[i]);
            i++;
        }
    }
	return (SUCCESS);
 }			