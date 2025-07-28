/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:45:04 by aherlaud          #+#    #+#             */
/*   Updated: 2025/07/28 16:46:55 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
