/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:27:12 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/01 15:08:16 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// CREER UN NVEAU MAILLON
// t_tok	*ft_lstnew_tok(TOK_TYPE type, char *word, t_shell *shell)
t_tok	*ft_lstnew_tok(TOK_TYPE type, char *word, t_shell *shell)
{
	t_tok	*new;

	new = malloc(sizeof(t_tok));
	if (new == NULL)
		free_exit(shell);
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

// AJOUTE LE NVEAU MAILLON A LA FIN DE LA LISTE
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
	t_tok	*current;
	t_tok	*tmp;

	current = lst;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->word);
		free(tmp);
	}
	lst = NULL;
}
