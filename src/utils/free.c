/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:29:14 by pandemonium       #+#    #+#             */
/*   Updated: 2025/06/29 15:40:22 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_all(t_shell *shell)
{
	(void)shell;
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
	if (PIPEX)
	{
		if (PIPEX->child_tab)
			free(PIPEX->child_tab);
		free(PIPEX);
	}
	if (shell->var)
		free(shell->var);
	if (shell->pid)
		free(shell->pid);
	if (shell)
		free(shell);
}