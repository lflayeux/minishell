/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:20:21 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/13 21:14:14 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_get_env(char **env, char *to_check)
{
	int		i;
	char	**split;

	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (ft_strcmp(split[0], to_check) == 0)
			return (ft_free_tab((void **)split), 1);
		ft_free_tab((void **)split);
		i++;
	}
	return (0);
}

void	expand_env(char **to_expand, t_shell *shell)
{
	t_expand	*expand;
	int			i;

	i = 0;
	expand = malloc(sizeof(t_expand));
	expand->new = NULL;
	expand->quotes = 0;
	if (!expand)
		return (free_error(shell));
	while (to_expand[i])
	{
		expand->word = to_expand[i];
		expanded_one(expand, shell);
		if (expand->new)
		{
			free(expand->word);
			to_expand[i] = ft_strdup(expand->new);
			if (!to_expand[i])
				return (free_error(shell));
			free(expand->new);
		}
		i++;
	}
	free(expand);
}

char	**put_env(t_shell *shell, char **env, char *cmd)
{
	int		len;
	int		j;
	char	**new_env;

	len = 0;
	j = 0;
	while (env[len])
		len++;
	new_env = malloc((len + 2) * sizeof(char *));
	if (!new_env)
		return (free_all(shell), exit(25), NULL);
	while (env[j])
	{
		new_env[j] = ft_strdup(env[j]);
		if (!new_env[j])
			return (ft_free_tab((void **)new_env), free_error(shell), NULL);
		j++;
	}
	new_env[j] = ft_strdup(cmd);
	if (!new_env[j])
		return (ft_free_tab((void **)new_env), free_error(shell), NULL);
	new_env[j + 1] = NULL;
	expand_env(new_env, shell);
	ft_free_tab((void **)(env));
	return (new_env);
}

int	manage_env(char *split, char *env, char *cmd, char **new_env)
{
	char	**split_2;

	split_2 = ft_split(env, '=');
	if (!split_2)
		return (FALSE);
	if (ft_strcmp(split_2[0], split) == 0)
	{
		free((*new_env));
		(*new_env) = ft_strdup(cmd);
	}
	else
	{
		free((*new_env));
		(*new_env) = ft_strdup(env);
	}
	ft_free_tab((void **)split_2);
	if (!(*new_env))
		return (FALSE);
	return (TRUE);
}

char	**set_env(t_shell *shell, char *split, char **env, char *cmd)
{
	int		j;
	char	**new_env;

	j = 0;
	new_env = init_env(shell, env);
	if (!split[0] || !new_env)
		return (NULL);
	while (env[j])
	{
		if (manage_env(split, env[j], cmd, &(new_env[j])) == FALSE)
			free_error(shell);
		j++;
	}
	ft_free_tab((void **)(env));
	return (new_env);
}
