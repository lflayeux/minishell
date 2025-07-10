/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:59:10 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/10 23:19:19 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// A renommer print_error apres changement de l'orioginale
void	print_error(char *s1, char *s2, t_shell *shell, int type)
{
	(void)shell;
	// dup2(2, 1);
	if (s1 && s2 && type != 0)
		printf("minishell: %s: %s\n", s1, s2);
	else if (s1 && s2)
		printf("minishell: %s: %s\n", s1, s2);
	else if (s1 && !s2)
		printf("minishell: %s\n", s1);
	signal_global = type;
}

int error_detected(t_tok *init)
{
	if (init->type != WORD && !(init->next))
	{
		if (TYPE == PIPE)
			ft_printf("missing command after a pipe\n");
		else
			ft_printf("error near unexpected token '\\n'\n");
		return (TRUE);
	}
	if (init->type != WORD && init->type != PIPE
		&& (init->next)->type != WORD)
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

t_tok	*parse_error(t_shell *shell)
{
	t_tok	*init;

	if (!shell->tok)
		return (NULL);
	init = shell->tok;
	if (TYPE == PIPE)
		return (print_error(PARSE_MESS,
				(char *)get_token_name(shell->tok->type), shell, 0), init);
	while (init)
	{
		if(error_detected(init) == TRUE)
			return (init);
		// if (init->type != WORD && !(init->next))
		// {
		// 	if (TYPE == PIPE)
		// 	{
		// 		ft_printf("missing command after a pipe\n");
		// 		return (init);
		// 	}
		// 	else
		// 	{
		// 		ft_printf("error near unexpected token '\\n'\n");
		// 		return (init);
		// 	}
		// }
		// if (init->type != WORD && init->type != PIPE
		// 	&& (init->next)->type != WORD)
		// {
		// 	ft_printf("error near unexpected token '%s'\n",
		// 		get_token_name((init->next)->type));
		// 	return (init);
		// }
		// if (init->type == PIPE && (init->next)->type == PIPE)
		// {
		// 	ft_printf("error near unexpected token '|'\n");
		// 	return (init);
		// }
		init = init->next;
	}
	return (NULL);
}
