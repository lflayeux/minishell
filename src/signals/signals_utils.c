/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:49:39 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/26 15:52:22 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_ctrl_c_interactive(int signal)
{
	if (signal != SIGINT)
		return ;
	g_signal_global = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_ctrl_c_action(int signal)
{
	if (signal != SIGINT)
		return ;
	g_signal_global = 130;
	printf("\n");
}

void handle_ctrl_c_here_doc(int signal) 
{
	if (signal != SIGINT)
		return ;
    write(STDOUT_FILENO, "\n", 1); // Print newline manually (non-reentrant safe)
	exit(130);	
}

void	handle_ctrl_c_quit(int signal)
{
	if (signal != SIGINT)
		return ;
	g_signal_global = 130;
}

void	handle_ctrl_dump(int signal)
{
	if (signal != SIGQUIT)
		return ;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}
