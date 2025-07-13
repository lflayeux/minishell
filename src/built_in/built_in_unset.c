/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:08:07 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/13 21:19:20 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_unset(char *unset_env, char **env, char ***new_env)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	j = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (!split)
			return (FALSE);
		if (ft_strcmp(split[0], unset_env))
		{
			(*new_env)[j] = ft_strdup(env[i]);
			if (!(*new_env)[j])
				return (ft_free_tab((void **)split), FALSE);
			j++;
		}
		ft_free_tab((void **)split);
		i++;
	}
	return (TRUE);
}

char	**unset_env(t_shell *shell, char *unset_env, char **env)
{
	char	**new_env;
	int		len;

	len = 0;
	while (env[len])
		len++;
	new_env = ft_calloc(len, sizeof(char *));
	if (new_env == NULL)
		return (free_error(shell), NULL);
	if (check_unset(unset_env, env, &new_env) == FALSE)
		return (ft_free_tab((void **)*new_env), free_error(shell), NULL);
	return (ft_free_tab((void **)env), new_env);
}

int	exec_unset(t_shell *shell, int i, t_exec *exec)
{
	char	**split;

	while (exec->cmd[i + 1])
	{
		split = ft_split(exec->cmd[i + 1], '=');
		if (!split)
			free_error(shell);
		if (ft_get_env(shell->env, split[0]))
			shell->env = unset_env(shell, shell->exec->cmd[i + 1], shell->env);
		if (!shell->env)
			return (ft_free_tab((void **)split), free_error(shell), 1);
		if (ft_get_env(shell->secret, split[0]))
			shell->secret = unset_env(shell, exec->cmd[i + 1], shell->secret);
		if (!shell->secret)
			return (ft_free_tab((void **)split), free_error(shell), 1);
		ft_free_tab((void **)split);
		i++;
	}
	return (SUCCESS);
}
