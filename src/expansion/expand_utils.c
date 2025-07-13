/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 19:22:45 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/13 17:29:10 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pid_expand(t_expand *expand, t_shell *shell)
{
	expand->i++;
	expand->new = ft_realloc(expand->new, strlen(expand->new)
			+ strlen(shell->pid) + 1);
	if (!expand->new)
		return (free_error(shell));
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
		return (free_error(shell));
	ft_strlcat(expand->new, error_str, strlen(expand->new) + strlen(error_str)
		+ 1);
	free(error_str);
}

void	base_expand(t_expand *expand, t_shell *shell)
{
	expand->new = ft_realloc(expand->new, strlen(expand->new) + 2);
	if (!expand->new)
		return (free_error(shell));
	expand->new[ft_strlen(expand->new)] = expand->word[expand->i];
	expand->i++;
}
