/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:59:10 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/03 16:15:59 by aherlaud         ###   ########.fr       */
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
		if (init->type != WORD && !(init->next))
		{
			if (TYPE == PIPE)
			{
				ft_printf("missing command after a pipe\n");
				// handle_ctrl_c_interactive(SIGINT);
				return (init);
			}
			else
			{
				ft_printf("error near unexpected token '\\n'\n");
				// handle_ctrl_c_interactive(SIGINT);
				return (init);
			}
		}
		if (init->type != WORD && init->type != PIPE
			&& (init->next)->type != WORD)
		{
			ft_printf("error near unexpected token '%s'\n",
				get_token_name((init->next)->type));
			// handle_ctrl_c_interactive(SIGINT);
			return (init);
		}
		if (init->type == PIPE && (init->next)->type == PIPE)
		{
			ft_printf("error near unexpected token '|'\n");
			return (init);
		}
		init = init->next;
	}
	return (NULL);
}
