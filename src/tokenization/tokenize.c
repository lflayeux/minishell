/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 12:19:00 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/06 15:47:18 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int is_symbol(char c)
{
    if (c == '<' || c == '>' || c == '|')
        return (1);
    return (0);    
}
int is_space(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' ||
            c == '\r')
        return (1);
    return (0);
}
int symbol_token(char *input, t_shell *shell)
{
    if (input[0] == '<')
    {
        if (input[1] && input[1] == '<')    
            return (ADD_TOK(&(shell->tok), NEW_TOK(HERE_DOC, NULL, shell)), 2);
        return (ADD_TOK(&(shell->tok), NEW_TOK(INFILE, NULL, shell)), 1);
    }
    else if (input[0] == '>')
    {
        if (input[1] && input[1] == '>') 
            return (ADD_TOK(&(shell->tok), NEW_TOK(APPEND, NULL, shell)), 2);
        return (ADD_TOK(&(shell->tok), NEW_TOK(OUTFILE, NULL, shell)), 1);
    }
    else if (input[0] == '|')
        return (ADD_TOK(&(shell->tok), NEW_TOK(PIPE, NULL, shell)), 1);
    return (0);
}

void    add_word_tok(char *input, t_shell *shell, char *word)
{
    int i;
    int j;
    int quotes;

    i = 0;
    j = 0;
    quotes = 0;
	while (input[i] != '\0')
	{
		if ((is_space(input[i]) || is_symbol(input[i])) && !quotes)
				break;
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
int len_word_tok(char *input)
{
    int i;
    int quotes;
    
    
    quotes = 0;
    i = 0;
	while (input[i] != '\0')
	{
		if ((is_space(input[i]) || is_symbol(input[i])) && !quotes)
				break;
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
int word_token(char *input, t_shell *shell)
{
    int     len;
    char    *word;
   
    len = 0;
    len += len_word_tok(input);
    word = calloc(len + 1, sizeof(char));
    if (!word)
        print_error(shell, MALLOC);
    add_word_tok(input, shell, word);
    printf("len : %d\n", len);
    return (len);
}

void    tokenize(t_shell *shell)
{
    int i;

    i = 0;
    while (shell->input[i])
	{
        if (is_space(shell->input[i]) )
            i++;
		else if (is_symbol(shell->input[i]))
            i += symbol_token(&(shell->input[i]), shell);
        else
            i += word_token(&(shell->input[i]), shell);
	}
}
