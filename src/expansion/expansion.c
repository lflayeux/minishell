	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:07:12 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/14 13:24:55 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	expand_word(t_expand *expand, t_shell *shell)
{
	expanded_one(expand, shell);
	if (expand->new)
	{
		free(expand->word);
		expand->word = expand->new;
		expand->new = NULL;
	}

	printf("%s\n", expand->word);
	expanded_two(expand, shell);
	if (expand->new)
	{
		free(expand->word);
		expand->word = expand->new;
	}
	printf("%s\n", expand->word);
}

void	expand(t_shell *shell)
{
	t_tok		*tmp;
	t_expand	*expand;

	tmp = shell->tok;
	expand = malloc(sizeof(t_expand));
	expand->new = NULL;
	expand->quotes = 0;
	if (!expand)
		print_error(shell, MALLOC);
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			expand->word = tmp->word;
			expand_word(expand, shell);
			tmp->word = expand->word;
		}
		if (shell->var)
		{
			free(shell->var);
			shell->var = NULL;
		}
		tmp = tmp->next;
	}
	free(expand);
}
