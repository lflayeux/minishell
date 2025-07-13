/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:33:04 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/13 17:04:56 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_symbol(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

void	add_word_tok(char *input, t_shell *shell, char *word)
{
	int	i;
	int	j;
	int	quotes;

	i = 0;
	j = 0;
	quotes = 0;
	while (input[i] != '\0')
	{
		if ((is_space(input[i]) || is_symbol(input[i])) && !quotes)
			break ;
		else if (input[i] == '\'' && quotes == 1)
			quotes = 0;
		else if (input[i] == '\'' && quotes == 0)
			quotes = 1;
		else if (input[i] == '"' && quotes == 2)
			quotes = 0;
		else if (input[i] == '"' && quotes == 0)
			quotes = 2;
		word[j++] = input[i++];
	}
	ADD_TOK(&(shell->tok), NEW_TOK(WORD, word, shell));
}

int	len_word_tok(char *input)
{
	int	i;
	int	quotes;

	quotes = 0;
	i = 0;
	while (input[i] != '\0')
	{
		if ((is_space(input[i]) || is_symbol(input[i])) && !quotes)
			break ;
		else if (input[i] == '\'' && quotes == 1)
			quotes = 0;
		else if (input[i] == '\'' && quotes == 0)
			quotes = 1;
		else if (input[i] == '"' && quotes == 2)
			quotes = 0;
		else if (input[i] == '"' && quotes == 0)
			quotes = 2;
		i++;
	}
	return (i);
}
