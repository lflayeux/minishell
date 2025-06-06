/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:07:12 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/06 19:24:43 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_dollar_valid(char *word)
{
	int i;
	int quotes;

	i = 0;
	quotes = 0;
	while (word[i])
	{
		if (word[i] == '$' && !quotes)
			return (1);
		else if (word[i] == '\'' && !quotes)
			quotes = 1;
		else if (word[i] == '\'' && quotes == 1)
			quotes = 0;
		i++;
	}
	return (0);
}

int	check_dollar(t_tok *token)
{
	int	i;
	t_tok	*tmp;

	i = 0;
	while (tmp)
	{
		if (tmp->word && is_dollar_valid(tmp->word))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	expand(t_shell *shell)
{
    while (check_dollar(shell))
		expand_dollar(shell);


    
}