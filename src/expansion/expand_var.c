/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:25:39 by aherlaud          #+#    #+#             */
/*   Updated: 2025/07/13 17:30:41 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	len_var_name(char *word, t_expand *expand, int *len)
{
	while (ft_isalnum(word[*len]) || word[*len] == '_')
	{
		(*len)++;
		if (expand)
			expand->i++;
	}
}

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
	len_var_name(word, expand, &len);
	while (env[++i])
	{
		if (!ft_strncmp(env[i], word, len) && env[i][len] == '=')
		{
			var = ft_strdup(&env[i][len + 1]);
			if (!var)
				free_error(shell);
			return (var);
		}
	}
	return (NULL);
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
			return (free_error(shell));
		return ;
	}
	expand->new = ft_realloc(expand->new, strlen(expand->new)
			+ strlen(shell->var) + 1);
	if (!expand->new)
		return (free_error(shell));
	ft_strlcat(expand->new, shell->var, strlen(expand->new) + strlen(shell->var)
		+ 1);
}
