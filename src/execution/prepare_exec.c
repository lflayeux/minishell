/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:31:21 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/13 13:32:46 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	tokken_choice(t_shell *shell, t_tok **init, t_exec *node_exec, int *i)
{
	if ((*init)->type == WORD)
	{
		(node_exec->cmd)[*i] = ft_strdup((*init)->word);
		if (!((node_exec->cmd)[*i]))
			return (free_error(shell), FALSE);
		(*i)++;
	}
	if ((*init)->type == INFILE && N->type == WORD && N)
		if_infile(node_exec, init);
	if ((*init)->type == OUTFILE && N->type == WORD && N)
		if_outfile(node_exec, init, shell);
	if ((*init)->type == APPEND && N->type == WORD && N)
		if_append(node_exec, init);
	if ((*init)->type == HERE_DOC && N->type == WORD && N)
	{
		if (if_here_doc(node_exec, init, shell) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

int	init_exec(t_tok *init, t_exec *node_exec, t_tok *end, t_shell *shell)
{
	int	i;

	i = 0;
	while (init && init != end)
	{
		if (tokken_choice(shell, &init, node_exec, &i) == FALSE)
			return (FALSE);
		init = init->next;
	}
	return (TRUE);
}

t_exec	*ft_lstnew_exec(t_tok *init, t_tok *end, t_shell *shell)
{
	t_exec	*node_exec;

	node_exec = malloc(sizeof(t_exec));
	if (!node_exec)
		return (free_all(shell), exit(25), NULL);
	exec_init(node_exec);
	node_exec->cmd = ft_calloc(word_number(init, end) + 1, sizeof(char *));
	if (!(node_exec->cmd))
		return (free(node_exec), free_error(shell), NULL);
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

int	find_target(t_tok **tmp_tok1, t_tok *tmp_error)
{
	while ((*tmp_tok1) && (*tmp_tok1)->type != PIPE)
	{
		if (tmp_error != NULL && (*tmp_tok1) == tmp_error)
			return (TRUE);
		(*tmp_tok1) = (*tmp_tok1)->next;
	}
	return (TRUE);
}

// CREATE THE LIST OF ALL EXEC TO MAKE
int	create_lst_exec(t_shell *shell)
{
	t_tok	*tmp_tok1;
	t_tok	*tmp_tok2;
	t_tok	*tmp_error;
	t_exec	*new;

	tmp_tok1 = shell->tok;
	tmp_tok2 = shell->tok;
	tmp_error = NULL;
	if(parse_error(shell, &tmp_error) == FALSE)
		return (FALSE);
	// if(!tmp_error)
	// 	return (FALSE);
	while (tmp_tok1)
	{
		if (find_target(&tmp_tok1, tmp_error) == FALSE)
			break;
			// break;
		new = NEW_EXEC(tmp_tok2, tmp_tok1, shell);
		if (!new)
			return (FALSE);
		ADD_BACK_EXEC(&(shell->exec), new);
		if (tmp_error != NULL && tmp_tok1 == tmp_error)
			return (FALSE);
		if (tmp_tok1 && tmp_tok1->type == PIPE)
			tmp_tok1 = tmp_tok1->next;
		// tmp_tok1 = tmp_tok1->next;
		tmp_tok2 = tmp_tok1;
		// tmp_tok2 = tmp_tok1;
	}
	return (TRUE);
}
