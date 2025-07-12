/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:59:10 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/12 13:53:18 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// A renommer print_error apres changement de l'orioginale
void	print_error(char *s1, char *s2, t_shell *shell, int type)
{
	(void)shell;
	if (s1 && s2 && type != 0)
		printf("minishell: %s: %s\n", s1, s2);
	else if (s1 && s2)
		printf("minishell: %s: %s\n", s1, s2);
	else if (s1 && !s2)
		printf("minishell: %s\n", s1);
	g_signal_global = type;
}

int	error_detected(t_tok *init)
{
	if (init->type != WORD && !(init->next))
	{
		if (TYPE == PIPE)
			ft_printf("missing command after a pipe\n");
		else
			ft_printf("error near unexpected token '\\n'\n");
		return (TRUE);
	}
	if (init->type != WORD && init->type != PIPE && (init->next)->type != WORD)
	{
		ft_printf("error near unexpected token '%s'\n",
			get_token_name((init->next)->type));
		return (TRUE);
	}
	if (init->type == PIPE && (init->next)->type == PIPE)
	{
		ft_printf("error near unexpected token '|'\n");
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
	if (TYPE == PIPE)
		return (print_error(PARSE_MESS,
				(char *)get_token_name(shell->tok->type), shell, 0), FALSE);
	while (init)
	{
		if (error_detected(init) == TRUE)
		{
			*error = init;
			return (TRUE);
		}
		init = init->next;
	}
	return (TRUE);
}
