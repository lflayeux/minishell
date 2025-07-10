/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:31:21 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/10 17:55:53 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_exec(t_tok *init, t_exec *node_exec, t_tok *end, t_shell *shell)
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
		{
			if (if_here_doc(node_exec, &init, shell) == FALSE)
				return (FALSE);
		}
		init = N;
	}
	return (TRUE);
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
	if (init_exec(init, node_exec, end, shell) == FALSE)
	{
		if (node_exec->cmd)
			ft_free_tab((void **)node_exec->cmd);
		if (node_exec)
			free(node_exec);
		return (NULL);
	}
	return (node_exec);
}

// int	activate_heredoc(t_tok *tok, t_shell *shell)
// {
// 	t_tok	*tmp;

// 	tmp = tok;
// 	while (tmp)
// 	{
// 		if (tmp->next && tmp->type == HERE_DOC && tmp->next->type == WORD)
// 			return (loop_here_doc(tmp->next->word, NULL, shell), 0);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

// CREATE THE LIST OF ALL EXEC TO MAKE
int	create_lst_exec(t_shell *shell)
{
	t_tok	*tmp_tok1;
	t_tok	*tmp_tok2;
	t_tok	*tmp_error;
	t_exec	*new;

	tmp_tok1 = shell->tok;
	tmp_tok2 = shell->tok;
	tmp_error = parse_error(shell);
	while (tmp_tok1)
	{
		while (tmp_tok1 && tmp_tok1->type != PIPE)
		{
			if (tmp_error != NULL && tmp_tok1 == tmp_error)
				break ;
			tmp_tok1 = tmp_tok1->next;
		}
		new = NEW_EXEC(tmp_tok2, tmp_tok1, shell);
		if (!new)
			return (FALSE);
		ADD_BACK_EXEC(&(shell->exec), new);
		if (tmp_error != NULL && tmp_tok1 == tmp_error)
			return (FALSE);
		if (tmp_tok1 && tmp_tok1->type == PIPE)
			tmp_tok1 = tmp_tok1->next;
		tmp_tok2 = tmp_tok1;
	}
	return (TRUE);
}
