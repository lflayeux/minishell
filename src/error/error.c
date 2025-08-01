/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:59:10 by lflayeux          #+#    #+#             */
/*   Updated: 2025/08/01 17:59:42 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// A renommer print_error apres changement de l'orioginale
void	print_error(char *s1, char *s2, t_shell *shell, int type)
{
	(void)shell;
	dup2(2, 1);
	if (s1 && s2 && type != 0)
		printf("minishell: %s: %s\n", s1, s2);
	else if (s1 && s2)
		printf("minishell: %s: %s\n", s1, s2);
	else if (s1 && !s2)
		printf("minishell: %s\n", s1);
	shell->error = type;
}

int	error_detected(t_tok *init, t_shell *shell)
{
	if (init->type != WORD && !(init->next))
	{
		if (init->type == PIPE)
			print_error("missing command after a pipe", NULL, shell, 1);
		else
			print_error("error near unexpected token '\\n'", NULL, shell, 1);
		return (TRUE);
	}
	if (init->type != WORD && init->type != PIPE && (init->next)->type != WORD)
	{
		print_error("error near unexpected token",
			(char *)get_token_name((init->next)->type), shell, 1);
		return (TRUE);
	}
	if (init->type == PIPE && (init->next)->type == PIPE)
	{
		print_error("error near unexpected token '|'", NULL, shell, 1);
		return (TRUE);
	}
	return (FALSE);
}

int	parse_error(t_shell *shell, t_tok **error)
{
	t_tok	*init;

	if (!shell->tok)
		return (FALSE);
	init = shell->tok;
	if (init->type == PIPE)
		return (print_error(PARSE_MESS,
				(char *)get_token_name(shell->tok->type), shell, 1), FALSE);
	while (init)
	{
		if (error_detected(init, shell) == TRUE)
		{
			*error = init;
			return (TRUE);
		}
		init = init->next;
	}
	return (TRUE);
}
