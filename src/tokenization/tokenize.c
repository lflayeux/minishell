/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:19:00 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/24 18:43:24 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	symbol_token(char *input, t_shell *shell)
{
	if (input[0] == '<')
	{
		if (input[1] && input[1] == '<')
			return (ft_lstadd_back_tok(&(shell->tok),
					ft_lstnew_tok(HERE_DOC, NULL, shell)), 2);
		return (ft_lstadd_back_tok(&(shell->tok),
				ft_lstnew_tok(INFILE, NULL, shell)), 1);
	}
	else if (input[0] == '>')
	{
		if (input[1] && input[1] == '>')
			return (ft_lstadd_back_tok(&(shell->tok),
					ft_lstnew_tok(APPEND, NULL, shell)), 2);
		return (ft_lstadd_back_tok(&(shell->tok),
				ft_lstnew_tok(OUTFILE, NULL, shell)), 1);
	}
	else if (input[0] == '|')
		return (ft_lstadd_back_tok(&(shell->tok),
				ft_lstnew_tok(PIPE, NULL, shell)), 1);
	return (0);
}

int	word_token(char *input, t_shell *shell)
{
	int		len;
	char	*word;

	len = 0;
	len += len_word_tok(input);
	word = ft_calloc(len + 1, sizeof(char));
	if (!word)
		free_error(shell);
	add_word_tok(input, shell, word);
	return (len);
}

int	is_close(char *input)
{
	int	i;
	int	quotes;

	i = 0;
	while (input[i])
	{
		quotes = '\0';
		if (input[i] == '\'' || input[i] == '"')
			quotes = input[i++];
		if (quotes != '\0')
		{
			while (input[i] != quotes && input[i])
				i++;
			if (input[i++] == quotes)
				continue ;
			return (FALSE);
		}
		else
			i++;
	}
	return (TRUE);
}

int	tokenize(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->input || is_close(shell->input) == FALSE)
		return (FALSE);
	while (shell->input[i])
	{
		if (is_space(shell->input[i]))
			i++;
		else if (is_symbol(shell->input[i]))
			i += symbol_token(&(shell->input[i]), shell);
		else
			i += word_token(&(shell->input[i]), shell);
	}
	return (TRUE);
}
