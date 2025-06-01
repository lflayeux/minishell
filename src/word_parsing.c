/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 14:07:09 by alex              #+#    #+#             */
/*   Updated: 2025/06/01 14:34:31 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// ==============================================
// =============== WORD PARSING =================
// ==============================================

int	is_openquotes(char **word, int index, char quote)
{
	int	i;
	char *tmp;

	tmp = *word;
	i = 0;
	while (i < index)
	{
		if (tmp[i] == quote)
			return (0);
		i++;
	}
	return (1);
}

int	add_dollar_env(char **word, char **new_word, int *i, int *j, t_shell **shell)
{
	int		l;
	char	*var_env;

	(*j)++;
	// printf("\t\t\t\t\t\t\t\t\t%d\n", is_openquotes(word, *j,'"'));
	if ((*word)[*j] == '\0' || ((*word)[*j] == '"' && is_openquotes(word, *j,
				'"') == 0))
	{
		var_env = ft_strdup("$\0");
		// printf("\t\t\t\t\t\t\t\t\tTEST\n");
		add_or_free(*shell, var_env, NULL, 0);		
	}
	else if ((*word)[*j] == '$')
	{
		var_env = get_pid(shell);
		(*j)++;
		// printf("pid : %ld\n", ft_strlen(get_pid()));
		// (*i)++;
	}
	else if (ft_isdelim((*word)[*j], "\'\""))
		return (0);
	else
	{
		var_env = getenv(find_var_spe(*word, *j, shell));
		(*j) += strlen(find_var_spe(*word, *j, shell));
		if (!var_env)
			return (0);
	}
	// var_env = check_dollar_env(word, j, env);
	// printf("\t\t\t\t\t\tTEST: %s\n", *word);
	l = 0;
	while (var_env[l])
	{
		(*new_word)[*i] = var_env[l];
		l++;
		(*i)++;
	}
	return (0);
}
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
