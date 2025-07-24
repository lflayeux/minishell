/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:46:44 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/24 19:35:38 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	word_number(t_tok *init, t_tok *end)
{
	t_tok	*tmp;
	int		count;

	tmp = init;
	count = 0;
	while (tmp && tmp != end)
	{
		if (tmp->type == WORD)
			count++;
		if (tmp->next && tmp->next != end && tmp->type != WORD)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	return (count);
}

int	if_here_doc(t_exec *node_exec, t_tok **init, t_shell *shell)
{
	// int end[2];
	
	if (pipe(node_exec->end) == -1)
		return (FALSE);
	// if (node_exec->here_doc)
	// 	ft_free_tab((void **)node_exec->here_doc);
	ignore_signals(shell->signals);
	if (loop_here_doc(node_exec, ((*init)->next)->word, shell) == FALSE)
		return (parent_signals(shell->signals), FALSE);
	// if (g_signal_global == 130)
	// 	return (parent_signals(shell->signals), FALSE);
	parent_signals(shell->signals);
	node_exec->if_here_doc = 1;
	node_exec->if_infile = 0;
	(*init) = ((*init)->next);
	return (TRUE);
}

int	if_append(t_exec *node_exec, t_tok **init)
{
	node_exec->outfile = ((*init)->next)->word;
	node_exec->if_append = 1;
	node_exec->if_outfile = 0;
	(*init) = ((*init)->next);
	return (TRUE);
}

int	if_outfile(t_exec *node_exec, t_tok **init, t_shell *shell)
{
	int	temp_fd;

	(void)shell;
	temp_fd = open(((*init)->next)->word, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (temp_fd)
		close(temp_fd);
	node_exec->outfile = ((*init)->next)->word;
	node_exec->if_outfile = 1;
	node_exec->if_append = 0;
	(*init) = ((*init)->next);
	return (TRUE);
}

int	if_infile(t_exec *node_exec, t_tok **init)
{
	node_exec->infile = ((*init)->next)->word;
	node_exec->if_infile = 1;
	(*init) = ((*init)->next);
	return (TRUE);
}
