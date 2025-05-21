/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:34:14 by aherlaud          #+#    #+#             */
/*   Updated: 2025/05/21 14:28:44 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// INITIALISE LA STRUCTURE EN FONCTION DE LA PRECEDENTE SI ELLE EXISTE
void	exec_init(t_exec *previous, t_exec *node_exec)
{
	node_exec->cmd = NULL;
	if (previous)
	{
		node_exec->infile = previous->infile;
		node_exec->outfile = previous->outfile;
		node_exec->if_infile = previous->if_infile;
		node_exec->if_outfile = previous->if_outfile;
	}
	else
	{
		node_exec->infile = NULL;
		node_exec->outfile = NULL;
		node_exec->if_infile = 0;
		node_exec->if_outfile = 0;
	}
	node_exec->pipe_to = NULL;
}

// CREATE STRUCT AND JOIN&SPLIT COMMAND APPEND AND HERE_DOC MISSING
t_exec	*ft_lstnew_exec(t_exec *previous, t_tok *init, t_tok *end)
{
	t_exec	*node_exec;
	char	*cmd;

	cmd = NULL;
	node_exec = malloc(sizeof(t_exec));
	exec_init(previous, node_exec);
	while (init && init != end)
	{
		if (init->type == WORD)
		{
			if (!cmd)
				cmd = ft_strdup("");
			else
				cmd = ft_strjoin(cmd, ft_strdup(" "));
			cmd = ft_strjoin(cmd, init->word);
		}
		if (init->type == INFILE && (init->next)->type == WORD && init->next)
		{
			node_exec->infile = (init->next)->word;
			node_exec->if_infile = 1;
			init = init->next;
		}
		if (init->type == OUTFILE && (init->next)->type == WORD && init->next)
		{
			node_exec->outfile = (init->next)->word;
			node_exec->if_outfile = 1;
			init = init->next;
		}
		init = init->next;
	}
	printf("\nsortie de boucle\n");
	if (cmd)
		node_exec->cmd = ft_split(cmd, ' ');
	else
		node_exec->cmd = NULL;
	return (node_exec);
}

// CREATE THE LIST OF ALL EXEC TO MAKE
void	create_lst_exec(t_exec **lst_exec, t_tok **token)
{
	t_tok	*tmp_tok1;
	t_tok	*tmp_tok2;

	tmp_tok1 = *token;
	tmp_tok2 = *token;
	while (tmp_tok1)
	{
		while (tmp_tok1 && tmp_tok1->type != PIPE)
			tmp_tok1 = tmp_tok1->next;
		ft_lstadd_back_exec(lst_exec, ft_lstnew_exec(ft_lstlast_exec(*lst_exec),
				tmp_tok2, tmp_tok1));
		if (tmp_tok1 && tmp_tok1->type == PIPE)
			tmp_tok1 = tmp_tok1->next;
		// printf("\t\t\t\t\t\t\tTEST\n");
		tmp_tok2 = tmp_tok1;
	}
}
