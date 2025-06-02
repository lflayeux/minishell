/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:52:30 by pandemonium       #+#    #+#             */
/*   Updated: 2025/06/02 19:59:30 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// ==============================================
// =============== WORD PARSING =================
// ==============================================

int	sin_quotes_exp(char **word, char **new_word, int *i, int *j)
{
	(*j)++;
	while ((*word)[*j] != '\'')
	{
		(*new_word)[*i] = (*word)[*j];
		(*i)++;
		(*j)++;
	}
	(*j)++;
	return (0);
}
int	dou_quotes_exp(char **word, char **new_word, int *i, int *j, t_shell **shell)
{
	(*j)++;
	while ((*word)[*j] != '"')
	{
		if ((*word)[*j] == '$')
		{
			add_dollar_env(word, new_word, i, j, shell);
			// if (add_dollar_env(word, new_word, i, j, shell) == -1)
				// return (-1);
		}
		else
		{
			(*new_word)[*i] = (*word)[*j];
			(*i)++;
			(*j)++;
		}
	}
	(*j)++;
	return (0);
}

int	expand_word(char **word, t_shell **shell)
{
	char	*new_word;
	int		i;
	int		j;

	// if (ft_strchr(*word, '$') && ft_strchr(*word, '\'') && ft_strchr(*word,
	// 		'"'))
	// 	return (0);
	new_word = ft_calloc(expansion_len(word, shell) + 1, sizeof(char));
	if (!new_word)
		free_exit(*shell);
	i = 0;
	j = 0;
	while (i < expansion_len(word, shell))
	{
		if ((*word)[j] == '\'')
			sin_quotes_exp(word, &new_word, &i, &j);
		else if ((*word)[j] == '$')
		{
			if (add_dollar_env(word, &new_word, &i, &j, shell) == -1)
				return (-1);
		}
		else if ((*word)[j] == '"')
			dou_quotes_exp(word, &new_word, &i, &j, shell);
		else
			new_word[i++] = (*word)[j++];
	}
	return (free(*word), *word = new_word, 0);
}

int	word_identification(t_shell **shell)
{
	t_tok	*tmp;

	tmp = (*shell)->tok;
	while (tmp)
	{
		if (tmp->type == WORD && (ft_strchr(tmp->word, '$')
				|| ft_strchr(tmp->word, '\'') || ft_strchr(tmp->word, '"')))
			expand_word(&(tmp->word), shell);
		tmp = tmp->next;
	}
	return (1);
}
