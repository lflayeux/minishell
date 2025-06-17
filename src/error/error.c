/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:59:10 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/17 18:50:47 by lflayeux         ###   ########.fr       */
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
}
int	parse_error(t_shell *shell)
{
	t_tok	*tmp_tok;

	tmp_tok = shell->tok;
	if(tmp_tok->type == PIPE)
		return (print_error(shell, SYNTAX_PIPE), 0);
	while (tmp_tok)
	{
		if (tmp_tok->type != WORD && (tmp_tok->next)->type != WORD)
		{
			if(tmp_tok->type == PIPE && !(tmp_tok->next))
			{
				ft_printf("missing command after a pipe");
				handle_ctrl_c_interactive(SIGINT);
				return (0);
			}

			ft_printf("syntax error near unexpected token '/\n'\n");
			handle_ctrl_c_interactive(SIGINT);
			return (0);
		}
		tmp_tok = tmp_tok->next;
	}
	return (1);
}