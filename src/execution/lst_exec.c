/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:52:48 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/11 11:32:12 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_exec	*ft_lstlast_exec(t_exec *lst)
{
	if (!lst)
		return (0);
	while (lst->pipe_to != NULL)
		lst = lst->pipe_to;
	return (lst);
}

// AJOUTE LE NVEAU MAILLON A LA FIN DE LA LISTE
void	ft_lstadd_back_exec(t_exec **token, t_exec *new)
{
	t_exec	*last;

	if (token == NULL)
		return ;
	if (*token == NULL)
	{
		*token = new;
		return ;
	}
	last = ft_lstlast_exec(*token);
	last->pipe_to = new;
}

void	del_node_exec(void *exec_node)
{
	t_exec	*exec;

	exec = (t_exec *)exec_node;
	if (exec->cmd)
		ft_free_tab((void **)(exec->cmd));
	if (exec->here_doc)
		ft_free_tab((void **)(exec->here_doc));
}

void	ft_lstclear_exec(t_exec *lst)
{
	t_exec *current;
	t_exec *tmp;

	current = lst;
	while (current)
	{
		tmp = current;
		current = current->pipe_to;
		del_node_exec(tmp);
		free(tmp);
	}
	lst = NULL;
}