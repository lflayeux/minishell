/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 12:43:40 by aherlaud          #+#    #+#             */
/*   Updated: 2025/05/29 15:32:20 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// CREER UN NVEAU MAILLON
t_malloc	*ft_lstnew_malloc(char **tab_str, char *str)
{
	t_malloc	*new;

	new = malloc(sizeof(t_malloc));
	if (new == NULL)
		return (0);
	new->tab = tab_str;
	new->str = str;
	new->next = NULL;
	return (new);
}

t_malloc	*ft_lstlast_malloc(t_malloc *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

// AJOUTE LE NVEAU MAILLON A LA FIN DE LA LISTE
void	ft_lstadd_back_malloc(t_malloc **token, t_malloc *new)
{
	t_malloc *last;

	if (token == NULL)
		return ;
	if (*token == NULL)
	{
		*token = new;
		return ;
	}
	last = ft_lstlast_malloc(*token);
	last->next = new;
}