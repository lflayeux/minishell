/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:26:35 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/02 10:55:01 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_ctrl_c_interactive(int signal)
{
	if (signal != SIGINT)
		return ;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_ctrl_c_action(int signal)
{
	if (signal != SIGINT)
		return ;
	printf("\n");
}

void	handle_ctrl_dump(int signal)
{
	if (signal != SIGQUIT)
		return ;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}
