/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 19:22:45 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/13 12:03:22 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_getenv(char **env, char *word, t_expand *expand, t_shell *shell)
{
	int		i;
	int		len;
	char	*var;

	i = -1;
	len = 0;
	if (!env || !shell)
		return (NULL);
	var = NULL;
	while (ft_isalnum(word[len]) || word[len] == '_')
	{
		len++;
		if (expand)
			expand->i++;
	}
	while (env[++i])
	{
		if (!ft_strncmp(env[i], word, len) && env[i][len] == '=')
		{
			var = ft_strdup(&env[i][len + 1]);
			return (var);
		}
	}
	return (NULL);
}

void	pid_expand(t_expand *expand, t_shell *shell)
{
	expand->i++;
	expand->new = ft_realloc(expand->new, strlen(expand->new)
			+ strlen(shell->pid) + 1);
	if (!expand->new)
		return (free_all(shell), exit(25));
	ft_strlcat(expand->new, shell->pid, strlen(expand->new) + strlen(shell->pid)
		+ 1);
}

void	error_expand(t_expand *expand, t_shell *shell)
{
	char	*error_str;

	expand->i++;
	error_str = ft_itoa((int)g_signal_global);
	if (!error_str)
		return (free_all(shell), exit(25));
	expand->new = ft_realloc(expand->new, strlen(expand->new)
			+ strlen(error_str) + 1);
	if (!expand->new)
		return (free_all(shell), exit(25));
	ft_strlcat(expand->new, error_str, strlen(expand->new) + strlen(error_str)
		+ 1);
	free(error_str);
}
void	base_expand(t_expand *expand, t_shell *shell)
{
	expand->new = ft_realloc(expand->new, strlen(expand->new) + 2);
	if (!expand->new)
		return (free_all(shell), exit(25));
	expand->new[ft_strlen(expand->new)] = expand->word[expand->i];
	expand->i++;
}

void	var_expand(t_expand *expand, t_shell *shell)
{
	if (shell->var)
		free(shell->var);
	shell->var = ft_getenv(shell->env, &(expand->word[expand->i]), expand,
			shell);
	if (shell->var == NULL)
	{
		while (expand->word[expand->i] && expand->word[expand->i] != ' '
			&& expand->word[expand->i] != '_'
			&& ft_isalnum(expand->word[expand->i]))
			expand->i++;
		expand->new = ft_realloc(expand->new, strlen(expand->new) + 2);
		if (!expand->new)
			return (free_all(shell), exit(25));
		return ;
	}
	expand->new = ft_realloc(expand->new, strlen(expand->new)
			+ strlen(shell->var) + 1);
	if (!expand->new)
		return (free_all(shell), exit(25));
	ft_strlcat(expand->new, shell->var, strlen(expand->new) + strlen(shell->var)
		+ 1);
}
