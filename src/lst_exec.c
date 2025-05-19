/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:54:28 by aherlaud          #+#    #+#             */
/*   Updated: 2025/05/19 16:02:16 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// CREER UN NVEAU MAILLON
t_exec	*ft_lstnew_exec(char **cmd)
{
	t_exec	*new;

	new = malloc(sizeof(t_exec));
	if (new == NULL)
		return (0);
	new->cmd = cmd;
	new->pipe_to = NULL;
	return (new);
}

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
	t_exec *last;

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