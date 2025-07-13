/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:20:21 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/13 13:31:25 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid_env(char *exec)
{
	int	i;

	i = 0;
	if (!exec || (!ft_isalpha(exec[0]) && exec[0] != '_'))
		return (0);
	while (exec[i] && exec[i] != '=')
	{
		if (!ft_isalnum(exec[i]) && exec[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
int	ft_get_env(char **env, char *to_check)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], to_check, ft_strlen(to_check)) == 0)
			return (1);
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
			if(!to_expand[i])
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

char	**set_env(t_shell *shell, char *split, char **env, char *cmd)
{
	int j;
	char **new_env;

	j = 0;
	new_env = init_env(shell, env);
	if (!split[0] || !new_env)
		return (NULL);
	while (env[j])
	{
		if (ft_strncmp(env[j], split, ft_strlen(split)) == 0)
		{
			free(new_env[j]);
			new_env[j] = ft_strdup(cmd);
		}
		else
		{
			free(new_env[j]);
			new_env[j] = ft_strdup(env[j]);
		}
		if(!new_env[j])
			free_error(shell);
		j++;
	}
	ft_free_tab((void **)(env));
	return (new_env);
}
