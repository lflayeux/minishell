/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 00:08:07 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/11 11:29:18 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**unset_env(char *unset_env, char **env)
{
	char	**new_env;
	char	**split;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = 0;
	while (env[len])
		len++;
	new_env = ft_calloc(len, sizeof(char *));
	if (new_env == NULL)
		return (NULL);
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (ft_strncmp(split[0], unset_env, ft_strlen(split[0])))
			new_env[j++] = ft_strdup(env[i]);
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
		if (GET_ENV(shell->env, split[0]))
			shell->env = unset_env(shell->exec->cmd[i + 1], shell->env);
		if (GET_ENV(shell->secret, split[0]))
			shell->secret = unset_env(exec->cmd[i + 1], shell->secret);
		ft_free_tab((void **)split);
		i++;
	}
	return (SUCCESS);
}