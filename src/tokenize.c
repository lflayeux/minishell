/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:21:43 by lflayeux          #+#    #+#             */
/*   Updated: 2025/05/27 11:19:14 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// ==============================================
// =============== TOKENISATION =================
// ==============================================

void	word_check_token(char **word, char **input)
{
	int		i;
	bool	s_quotes;
	bool	d_quotes;

	i = 0;
	s_quotes = false;
	d_quotes = false;
	while (**input != '\0')
	{
		if ((**input == ' ' || **input == '>' ||  **input == '<' ||
			**input == '|') && (s_quotes == false && d_quotes == false))
				break;
		else if (**input == '\'' && d_quotes == false)
			s_quotes = !s_quotes;
		else if (**input == '"' && s_quotes == false)
			d_quotes = !d_quotes;
		(*word)[i++] = *(*input)++;
	}
}

// AJOUTE UN MAILLON AVEC QUOTE ADEQUAT SI NECESSAIRE
void	word_token(char **input, t_tok **token)
{
	char	*word;
	int		len;

	len = 0;
	while ((*input)[len] != ' ' && (*input)[len] != '>' && (*input)[len] != '<' && (*input)[len] != '|' && (*input)[len] != '\0')
		len++;
	word = ft_calloc(len + 1, sizeof(char));
// TROUVER LA RETOUR A METTRE
	if (word == NULL)
		return ;
	word_check_token(&word, input);
	ft_lstadd_back_tok(token, ft_lstnew_tok(WORD, word));
}

// AJOUTE UN MAILLON AVEC REDIREC ADEQUAT
void	redir_token(char **input, t_tok **token, char redir)
{
	if ((*input)[1] && (*input)[1] == redir)
	{
		if (redir == '<')
			ft_lstadd_back_tok(token, ft_lstnew_tok(HERE_DOC, NULL));
		else
			ft_lstadd_back_tok(token, ft_lstnew_tok(APPEND, NULL));
		(*input)++;
	}
	else
	{
		if (redir == '<')
			ft_lstadd_back_tok(token, ft_lstnew_tok(INFILE, NULL));
		else
			ft_lstadd_back_tok(token, ft_lstnew_tok(OUTFILE, NULL));
	}
	(*input)++;
}

// CREER LA LISTE CHAINEE AVEC LE BON TYPE DE TOKEN
void    tokenize(char **input, t_tok **token)
{
	while (**input)
	{
		if (**input == ' ' && **input != '\0')
			(*input)++;
		else if (**input == '|')
		{
			ft_lstadd_back_tok(token, ft_lstnew_tok(PIPE, NULL));
			(*input)++;
		}
		else if (**input == '<')
			redir_token(input, token, '<');
		else if (**input == '>')
			redir_token(input, token, '>');
		else
			word_token(input, token);
	}
}