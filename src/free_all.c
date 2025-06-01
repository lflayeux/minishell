/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:32:56 by aherlaud          #+#    #+#             */
/*   Updated: 2025/06/01 11:22:51 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_all(t_shell *shell)
{
	// if (shell->signals)
	//     free(signals);
	if (shell->tok)
		ft_lstclear_tok(shell->tok);
	if (shell->exec)
		ft_lstclear_exec(shell->exec);
	// if (shell->malloc)
	// 	ft_lstclear_malloc(shell->malloc);
	// if (shell->env)
	// 	ft_free_tab((void **)(shell->env));
	if (shell->secret)
		ft_free_tab((void **)(shell->secret));
	if (shell->child_tab)
		ft_free_tab((void **)(shell->child_tab));
}

int free_exit(t_shell *shell)
{
	ft_free_all(shell);
	printf("\t\t\t\t\t\t\t\tTEST\n");
	// pritnf
	// code erreur à changer
	exit(1);
	return (1);
}

void	add_or_free(t_shell *shell, char *str, char **tab_str, int flag)
{
	if (flag == 0)
	{
		if (!str)
			free_exit(shell);
		else
			ft_lstadd_back_malloc(&(shell->malloc), ft_lstnew_malloc(NULL,
					str, shell));
	}
	else
	{
		if (!tab_str)
			free_exit(shell);
		else
			ft_lstadd_back_malloc(&(shell->malloc), ft_lstnew_malloc(tab_str,
					NULL, shell));
	}
}

