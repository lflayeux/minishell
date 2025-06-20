/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 19:22:45 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/20 16:29:05 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_getenv(char **env, char *word, t_expand *expand, t_shell *shell)
{
	int		i = 0;
	int		len = 0;
	char	*var;

	if (!env || !shell)
		return (NULL);
	while (ft_isalnum(word[len]) || word[len] == '_')
	{
		len++;
		if (expand)
			expand->i++;
	}
	while (env[i])
	{
		if (!ft_strncmp(env[i], word, len) && env[i][len] == '=')
		{
			var = ft_strdup(&env[i][len + 1]);
			if (!var)
				print_error("malloc", NULL, shell, GEN_ERROR);
		}
		i++;
	}
	return (var);
}

void	pid_expand(t_expand *expand, t_shell *shell)
{
	expand->i++;
	expand->new = ft_realloc(expand->new, strlen(expand->new) + strlen(shell->pid) + 1);
	if (!expand->new)
		print_error("malloc", NULL, shell, GEN_ERROR);
	ft_strlcat(expand->new, shell->pid, strlen(expand->new) + strlen(shell->pid) + 1);
}

void	error_expand(t_expand *expand, t_shell *shell)
{
	char	*error_str;

	expand->i++;
	error_str = ft_itoa((int)shell->error);
	if (!error_str)
		print_error("malloc", NULL, shell, GEN_ERROR);
	expand->new = ft_realloc(expand->new, strlen(expand->new) + strlen(error_str) + 1);
	if (!expand->new)
		print_error("malloc", NULL, shell, GEN_ERROR);
	ft_strlcat(expand->new, error_str, strlen(expand->new) + strlen(error_str) + 1);
	free(error_str);
}
void	base_expand(t_expand *expand, t_shell *shell)
{
	expand->new = ft_realloc(expand->new, strlen(expand->new) + 2);
	if (!expand->new)
		print_error("malloc", NULL, shell, GEN_ERROR);
	expand->new[ft_strlen(expand->new)] = expand->word[expand->i];
	expand->i++;
}

void	var_expand(t_expand *expand, t_shell *shell)
{

	shell->var = ft_getenv(shell->env, &(expand->word[expand->i]), expand, shell);
	if (shell->var == NULL)
	{
		base_expand(expand, shell);
		return ;
	}
	expand->new = ft_realloc(expand->new, strlen(expand->new) + strlen(shell->var) + 1);
	if (!expand->new)
		print_error("malloc", NULL, shell, GEN_ERROR);
	ft_strlcat(expand->new, shell->var, strlen(expand->new) + strlen(shell->var) + 1);
}
