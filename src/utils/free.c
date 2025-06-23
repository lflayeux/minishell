/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:29:14 by pandemonium       #+#    #+#             */
/*   Updated: 2025/06/23 11:31:43 by lflayeux         ###   ########.fr       */
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
	if (PIPEX)
	{
		if (PIPEX->child_tab)
			ft_free_tab((void**)PIPEX->child_tab);
		free(PIPEX);
	}
	if (shell->var)
		free(shell->var);
	if (shell->pid)
		free(shell->pid);
	if (shell)
		free(shell);
}