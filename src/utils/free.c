/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:29:14 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/13 12:14:28 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_rest(t_shell *shell)
{
	if (PIPEX)
	{
		if (PIPEX->child_tab)
			free(PIPEX->child_tab);
		PIPEX->child_tab = NULL;
		free(PIPEX);
	}
	if (shell->var)
		free(shell->var);
	if (shell->pid)
		free(shell->pid);
	if (shell)
		free(shell);
}

void	free_all(t_shell *shell)
{
	// (void)shell;
	if(PIPEX)
		close_fd(shell, 2, 0);
	if (shell->input)
		free(shell->input);
	if (shell->signals)
		free(shell->signals);
	if (shell->tok)
		ft_lstclear_tok(shell->tok);
	if (shell->exec)
		ft_lstclear_exec(shell->exec);
	if (shell->env)
		ft_free_tab((void **)shell->env);
	if (shell->secret)
		ft_free_tab((void **)shell->secret);
	free_rest(shell);
}

void free_error(t_shell *shell)
{
	free_all(shell);
	exit(25);
}