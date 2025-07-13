/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:08:07 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/13 13:26:09 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**unset_env(t_shell *shell, char *unset_env, char **env, int j)
{
	char	**new_env;
	char	**split;
	int		len;
	int 	i;

	len = 0;
	i = 0;
	while (env[len])
		len++;
	new_env = ft_calloc(len, sizeof(char *));
	if (new_env == NULL)
		return (free_error(shell), NULL);
	while (env[i])
	{
		split = ft_split(env[i], '=');
        if (!split)
            return (ft_free_tab((void **)new_env), free_error(shell), NULL);
		if (ft_strncmp(split[0], unset_env, ft_strlen(split[0])))
		{
			new_env[j] = ft_strdup(env[i]);
			if(!new_env[j])	
				return (ft_free_tab((void **)new_env), ft_free_tab((void **)split), free_error(shell), NULL);
			j++;
		}
		ft_free_tab((void **)split);
		i++;
	}
	ft_free_tab((void **)env);
	return (new_env);
}

int	exec_unset(t_shell *shell, int i, t_exec *exec)
{
	char **split;

	while (exec->cmd[i + 1])
	{
		split = ft_split(exec->cmd[i + 1], '=');
        if (!split)
            free_error(shell);
		if (GET_ENV(shell->env, split[0]))
			shell->env = unset_env(shell, shell->exec->cmd[i + 1], shell->env, 0);
        if (!shell->env)
            return (ft_free_tab((void **)split), free_error(shell), 1);
		if (GET_ENV(shell->secret, split[0]))
			shell->secret = unset_env(shell, exec->cmd[i + 1], shell->secret, 0);
        if (!shell->secret)
            return (ft_free_tab((void **)split), free_error(shell), 1);
		ft_free_tab((void **)split);
		i++;
	}
	return (SUCCESS);
}