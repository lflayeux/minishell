/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:31:21 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/25 12:10:08 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_exec(t_tok *init, t_exec *node_exec, t_tok *end, t_shell *shell)
{
	int	i;

	i = 0;
	while (init && init != end)
	{
		if (TYPE == WORD)
		{
			(node_exec->cmd)[i] = ft_strdup(init->word);
			if (!((node_exec->cmd)[i]))
				print_error("malloc", NULL, shell, GEN_ERROR);
			i++;
		}
		if (TYPE == INFILE && N->type == WORD && N)
			if_infile(node_exec, &init);
		if (TYPE == OUTFILE && N->type == WORD && N)
			if_outfile(node_exec, &init, shell);
		if (TYPE == APPEND && N->type == WORD && N)
			if_append(node_exec, &init);
		if (TYPE == HERE_DOC && N->type == WORD && N)
			if_here_doc(node_exec, &init);
		init = N;
	}
}
t_exec	*ft_lstnew_exec(t_tok *init, t_tok *end, t_shell *shell)
{
	t_exec	*node_exec;

	node_exec = malloc(sizeof(t_exec));
	if (!node_exec)
		print_error("malloc", NULL, shell, GEN_ERROR);
	exec_init(node_exec);
	node_exec->cmd = ft_calloc(word_number(init, end) + 1, sizeof(char *));
	if (!(node_exec->cmd))
		print_error("malloc", NULL, shell, GEN_ERROR);
	init_exec(init, node_exec, end, shell);
	return (node_exec);
}

int	activate_heredoc(t_tok *tok)
{
	t_tok	*tmp;

	tmp = tok;
	while (tmp)
	{
		if (tmp->next && tmp->type == HERE_DOC && tmp->next->type == WORD)
			return (loop_here_doc(tmp->next->word, NULL), 0);
		tmp = tmp->next;
	}
	return (0);
}

// CREATE THE LIST OF ALL EXEC TO MAKE
int	create_lst_exec(t_shell *shell)
{
	t_tok	*tmp_tok1;
	t_tok	*tmp_tok2;

	if (parse_error(shell) == 0)
		return (activate_heredoc(shell->tok), 0);
	// return (0);
	tmp_tok1 = shell->tok;
	tmp_tok2 = shell->tok;
	while (tmp_tok1)
	{
		while (tmp_tok1 && tmp_tok1->type != PIPE)
			tmp_tok1 = tmp_tok1->next;
		ADD_BACK_EXEC(&(shell->exec), NEW_EXEC(tmp_tok2, tmp_tok1, shell));
		if (tmp_tok1 && tmp_tok1->type == PIPE)
			tmp_tok1 = tmp_tok1->next;
		tmp_tok2 = tmp_tok1;
	}
	return (1);
}
