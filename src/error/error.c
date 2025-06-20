/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:59:10 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/20 16:45:46 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// A renommer print_error apres changement de l'orioginale
void    print_error(char *s1, char *s2, t_shell *shell, int type)
{
	shell->error = type;
	if (s1 && s2)
		printf("minishell: %s: %s: %s\n", s1, s2, strerror(errno));
	else if (s1 && !s2)
		printf("minishell: %s: %s\n", s1, strerror(errno));
	
}
int	parse_error(t_shell *shell)
{
	t_tok	*init;

	init = shell->tok;
	if(TYPE == PIPE)
		return (print_error(PARSE_MESS, (char *)get_token_name(shell->tok->type), shell, GEN_ERROR), FALSE);
	while (init)
	{
		if(TYPE == PIPE && !(init->next))
		{
			ft_printf("missing command after a pipe");
			// handle_ctrl_c_interactive(SIGINT);
			return (0);
		}
		else if ((TYPE == INFILE || TYPE == OUTFILE || TYPE == APPEND || TYPE == HERE_DOC) && !(init->next))
		{
			ft_printf("syntax error near unexpected token '\\n'\n");
			// handle_ctrl_c_interactive(SIGINT);
			return (0);
		}
		init = init->next;
	}
	return (1);
}
