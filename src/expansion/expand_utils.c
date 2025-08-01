/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 19:22:45 by lflayeux          #+#    #+#             */
/*   Updated: 2025/08/01 17:30:13 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pid_expand(t_expand *expand, t_shell *shell)
{
	expand->i++;
	expand->new = ft_realloc(expand->new, ft_strlen(expand->new)
			+ ft_strlen(shell->pid) + 1);
	if (!expand->new)
		return (free_error(shell));
	ft_strlcat(expand->new, shell->pid, ft_strlen(expand->new)
		+ ft_strlen(shell->pid) + 1);
}

void	error_expand(t_expand *expand, t_shell *shell)
{
	char	*error_str;

	expand->i++;
	if (g_signal_global == 130)
		shell->error = 130;
	g_signal_global = 0;
	error_str = ft_itoa(shell->error);
	if (!error_str)
		return (free_all(shell), exit(25));
	shell->error = 0;
	expand->new = ft_realloc(expand->new, ft_strlen(expand->new)
			+ ft_strlen(error_str) + 1);
	if (!expand->new)
		return (free_error(shell));
	ft_strlcat(expand->new, error_str, ft_strlen(expand->new)
		+ ft_strlen(error_str) + 1);
	free(error_str);
}

void	base_expand(t_expand *expand, t_shell *shell)
{
	expand->new = ft_realloc(expand->new, ft_strlen(expand->new) + 2);
	if (!expand->new)
		return (free_error(shell));
	expand->new[ft_strlen(expand->new)] = expand->word[expand->i];
	expand->i++;
}
