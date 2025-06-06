/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 22:16:13 by pandemonium       #+#    #+#             */
/*   Updated: 2025/06/06 12:03:55 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	reset_shell(t_shell *shell)
{
	if (shell->tok)
	{
		ft_lstclear_tok(shell->tok);
		shell->tok = NULL;
	}
	if (shell->input)
		free(shell->input);
	if (shell->signals)
		reset_signals(shell->signals);
}

void	init_shell(t_shell *shell, char **envp)
{
	(void)envp;
	shell->signals = malloc(sizeof(t_signal));
	set_signal(shell->signals);
	shell->tok = NULL;
	shell->input = NULL;
}
