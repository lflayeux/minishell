/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:34:14 by aherlaud          #+#    #+#             */
/*   Updated: 2025/05/19 23:59:49 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void exec_init(t_exec *node_exec)
{
	node_exec->cmd = NULL;
	node_exec->infile = NULL;
	node_exec->outfile = NULL;
	node_exec->if_infile = 0;
	node_exec->if_outfile = 0;
	node_exec->pipe_to = NULL;
}

t_exec	*ft_lstnew_exec(t_tok *init, t_tok *end)
{
	t_exec	*node_exec;
	char *cmd;

	cmd = NULL;
	node_exec = malloc(sizeof(t_exec));
	exec_init(node_exec);
	while (init && init != end)
	{
		if (init->type == WORD)
		{
			if(!cmd)
				cmd = ft_strdup("");
			else
				cmd = ft_strjoin(cmd, ft_strdup(" "));
			cmd = ft_strjoin(cmd, init->word);
		}
		if(init->type == INFILE && (init->next)->type == WORD)
		{
			node_exec->infile = (init->next)->word;		
			node_exec->if_infile = 1;
		}
		if(init->type == OUTFILE && (init->next)->type == WORD)
		{
			node_exec->outfile = (init->next)->word;		
			node_exec->if_outfile = 1;
		}
		init = init->next;
	}
	node_exec->cmd = ft_split(cmd, ' ');
	return (node_exec);
}

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
		ft_lstadd_back_exec(lst_exec, ft_lstnew_exec(tmp_tok2, tmp_tok1));
		if (tmp_tok1 && tmp_tok1->type == PIPE)
			tmp_tok1 = tmp_tok1->next;
		// printf("\t\t\t\t\t\t\tTEST\n");
		tmp_tok2 = tmp_tok1;
	}
}
