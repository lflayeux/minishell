/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 23:30:08 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/11 11:46:09 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tok	*ft_lstnew_tok(TOK_TYPE type, char *word, t_shell *shell)
{
	t_tok	*new;

	new = malloc(sizeof(t_tok));
	if (new == NULL)
		print_error("malloc", NULL, shell, GEN_ERR);
	new->type = type;
	new->word = word;
	new->next = NULL;
	return (new);
}

t_tok	*ft_lstlast_tok(t_tok *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_tok(t_tok **token, t_tok *new)
{
	t_tok	*last;

	if (token == NULL)
		return ;
	if (*token == NULL)
	{
		*token = new;
		return ;
	}
	last = ft_lstlast_tok(*token);
	last->next = new;
}

void	ft_lstclear_tok(t_tok *lst)
{
	t_tok *current;
	t_tok *tmp;

	if (!lst)
		return ;
	current = lst;
	while (current)
	{
		tmp = current;
		current = current->next;
		if (tmp->word)
			free(tmp->word);
		free(tmp);
	}
	lst = NULL;
}