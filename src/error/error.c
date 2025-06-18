/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:59:10 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/18 15:56:31 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    print_error(t_shell *shell, ERROR_TYPE err)
{
    if (err == MALLOC)
    {
        printf("minishell: allocation error");
        free_all(shell);
        exit(1);
	}
	else if (err == SYNTAX_PIPE)
	{
		ft_printf("syntax error near unexpected token '|'\n"); 
		handle_ctrl_c_interactive(SIGINT);
	}
	else if (err == OPEN)
	{
		printf("OPEN ERROR");	
	}
}
int	parse_error(t_shell *shell)
{
	t_tok	*init;

	init = shell->tok;
	if(TYPE == PIPE)
		return (print_error(shell, SYNTAX_PIPE), 0);
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
