/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:31:21 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/17 18:55:48 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:34:14 by aherlaud          #+#    #+#             */
/*   Updated: 2025/06/01 15:00:08 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int word_number(t_tok *init, t_tok *end)
{
	t_tok *tmp;
	int count;

	tmp = init;
	count = 0;
	while(tmp && tmp != end)
	{
		if(tmp->type == WORD)
			count++;
		if(tmp->next && tmp->next != end && tmp->type != WORD)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	return (count);
}
int	if_here_doc(t_exec *node_exec, t_tok **init)
{
	node_exec->delimiter = ((*init)->next)->word;
	node_exec->if_here_doc = 1;
	node_exec->if_infile = 0;
	(*init) = ((*init)->next);
	return (1);
}

int	if_append(t_exec *node_exec, t_tok **init)
{
	node_exec->outfile = ((*init)->next)->word;
	node_exec->if_append = 1;
	node_exec->if_outfile = 0;
	(*init) = ((*init)->next);
	return (1);
}

int	if_outfile(t_exec *node_exec, t_tok **init, t_shell *shell)
{
	int	temp_fd;

	temp_fd = open(((*init)->next)->word, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (temp_fd == -1)
		free_all(shell);
	close(temp_fd);
	node_exec->outfile = ((*init)->next)->word;
	node_exec->if_outfile = 1;
	node_exec->if_append = 0;
	(*init) = ((*init)->next);
	return (1);
}

int	if_infile(t_exec *node_exec, t_tok **init)
{
	node_exec->infile = ((*init)->next)->word;
	node_exec->if_infile = 1;
	(*init) = ((*init)->next);
	return (1);
}


// CREATE STRUCT AND JOIN&SPLIT COMMAND APPEND AND HERE_DOC MISSING
t_exec	*ft_lstnew_exec(t_tok *init, t_tok *end, t_shell *shell)
{
	t_exec	*node_exec;
	int i;

	node_exec = malloc(sizeof(t_exec));
	if(!node_exec)
		free_all(shell);
	exec_init(node_exec);
	node_exec->cmd = ft_calloc(word_number(init, end) + 1, sizeof(char *));
	if(!(node_exec->cmd))
		free_all(shell);
	i = 0;
	while (init && init != end)
	{
		if (init->type == WORD)
		{
			(node_exec->cmd)[i] = ft_strdup(init->word);
			if(!((node_exec->cmd)[i]))
				free_all(shell);;
			i++;
		}
		if (init->type == INFILE && (init->next)->type == WORD && init->next)
			if_infile(node_exec, &init);
		if (init->type == OUTFILE && (init->next)->type == WORD && init->next)
			if_outfile(node_exec, &init, shell);
		if (init->type == APPEND && (init->next)->type == WORD && init->next)
			if_append(node_exec, &init);
		if (init->type == HERE_DOC && (init->next)->type == WORD && init->next)
			if_here_doc(node_exec, &init);
		init = init->next;
	}
	return (node_exec);
}


// CREATE THE LIST OF ALL EXEC TO MAKE
void	create_lst_exec(t_shell *shell)
{
	t_tok	*tmp_tok1;
	t_tok	*tmp_tok2;

	//  pas fini
	if (parse_error(shell) == 0)
		return ;
	tmp_tok1 = shell->tok;
	tmp_tok2 = shell->tok;
	while (tmp_tok1)
	{
		while (tmp_tok1 && tmp_tok1->type != PIPE)
			tmp_tok1 = tmp_tok1->next;
		ft_lstadd_back_exec(&(shell->exec), ft_lstnew_exec(tmp_tok2, tmp_tok1, shell));
		if (tmp_tok1 && tmp_tok1->type == PIPE)
			tmp_tok1 = tmp_tok1->next;
		// printf("\t\t\t\t\t\t\tTEST\n");
		tmp_tok2 = tmp_tok1;
	}
}
