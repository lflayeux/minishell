/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:59:10 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/29 12:40:06 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// A renommer print_error apres changement de l'orioginale
void	print_error(char *s1, char *s2, t_shell *shell, int type)
{
	if (s1 && s2 && type != 0)
		printf("minishell: %s: %s: %s\n", s1, s2, strerror(errno));
	else if (s1 && s2)
		printf("minishell: %s: %s\n", s1, s2);
	else if (s1 && !s2)
		printf("minishell: %s: %s\n", s1, strerror(errno));
	shell->error = type;
}

int	parse_error(t_shell *shell)
{
	t_tok	*init;

	if (!shell->tok)
		return (FALSE);
	init = shell->tok;
	if (TYPE == PIPE)
		return (print_error(PARSE_MESS, (char *)get_token_name(shell->tok->type), shell, 0), FALSE);
	while (init)
	{
		if (init->type != WORD && !(init->next))
		{
			if (TYPE == PIPE)
			{
				ft_printf("missing command after a pipe\n");
				// handle_ctrl_c_interactive(SIGINT);
				return (0);
			}
			else
			{
				ft_printf(" error near unexpected token '\\n'\n");
				// handle_ctrl_c_interactive(SIGINT);
				return (0);
			}
		}
		if (init->type != WORD && (init->next)->type != WORD)
		{
			ft_printf(" error near unexpected token '%s'\n",
				get_token_name((init->next)->type));
			// handle_ctrl_c_interactive(SIGINT);
			return (0);
		}
		init = init->next;
	}
	return (1);
}
