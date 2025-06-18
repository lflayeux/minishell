/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:29:14 by pandemonium       #+#    #+#             */
/*   Updated: 2025/06/18 14:29:37 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_all(t_shell *shell)
{
	(void)shell;
	if (shell->signals)
		free(shell->signals);
	if (shell->tok)
		ft_lstclear_tok(shell->tok);
	if (shell->exec)
		ft_lstclear_exec(shell->exec);
	if (shell->env)
		ft_free_tab((void **)shell->env);
	if (shell->var)
		free(shell->var);
	if (shell->pid)
		free(shell->pid);
	if (shell)
		free(shell);
}