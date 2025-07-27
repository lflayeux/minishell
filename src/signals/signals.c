/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 21:49:02 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/27 19:57:05 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_signal(t_signal *signals)
{
	sigemptyset(&signals->ctrl_c.sa_mask);
	signals->ctrl_c.sa_flags = 0;
	signals->ctrl_c.sa_handler = handle_ctrl_c_interactive;
	sigaction(SIGINT, &signals->ctrl_c, NULL);
	sigemptyset(&signals->ctrl_dump.sa_mask);
	signals->ctrl_dump.sa_flags = 0;
	signals->ctrl_dump.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &signals->ctrl_dump, NULL);
}

void	parent_signals(t_signal *signals)
{
	signals->ctrl_c.sa_handler = handle_ctrl_c_action;
	sigaction(SIGINT, &signals->ctrl_c, NULL);
	signals->ctrl_dump.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &signals->ctrl_dump, NULL);
}

void	child_signals(t_signal *signals)
{
	signals->ctrl_dump.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &signals->ctrl_dump, NULL);
	signals->ctrl_c.sa_handler = handle_ctrl_c_quit;
	sigaction(SIGINT, &signals->ctrl_c, NULL);
}

void	here_doc_signals(t_signal *signals)
{
	signals->ctrl_dump.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &signals->ctrl_dump, NULL);
	signals->ctrl_c.sa_handler = handle_ctrl_c_here_doc;
	sigaction(SIGINT, &signals->ctrl_c, NULL);
}

void	reset_signals(t_signal *signals)
{
	signals->ctrl_c.sa_handler = handle_ctrl_c_interactive;
	sigaction(SIGINT, &signals->ctrl_c, NULL);
	signals->ctrl_dump.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &signals->ctrl_dump, NULL);
}

void	ignore_signals(t_signal *signals)
{
	signals->ctrl_c.sa_handler = SIG_IGN;
	sigaction(SIGINT, &signals->ctrl_c, NULL);
	signals->ctrl_dump.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &signals->ctrl_dump, NULL);
}
