/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_part.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:51:37 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/13 12:01:19 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	dollar_expand(t_expand *expand, t_shell *shell)
{
	expand->i++;
	if ((expand->word[expand->i] == '"' || expand->word[expand->i] == '\0')
		&& expand->quotes)
	{
		expand->i--;
		base_expand(expand, shell);
	}
	else if (expand->word[expand->i] == '$')
		pid_expand(expand, shell);
	else if (expand->word[expand->i] == '?')
		error_expand(expand, shell);
	else if (expand->word[expand->i] == '"' || expand->word[expand->i] == '\'')
		return ;
	else if (ft_isalnum(expand->word[expand->i])
		|| expand->word[expand->i] == '_')
		var_expand(expand, shell);
	else
	{
		expand->i--;
		base_expand(expand, shell);
	}
}

void	quotes_expand(t_expand *expand, char sep, t_shell *shell)
{
	size_t	new_len;
	int		start;

	expand->i++;
	start = expand->i;
	while (expand->word[expand->i] != sep && expand->word[expand->i])
	{
		if (expand->word[expand->i] == '$' && sep == '"')
			break ;
		expand->i++;
	}
	new_len = ft_strlen(expand->new) + (expand->i - start) + 1;
	expand->new = ft_realloc(expand->new, new_len);
	if (expand->new == NULL)
		return (free_all(shell), exit(25));
	ft_memcpy(expand->new + ft_strlen(expand->new), &(expand->word[start]),
		expand->i - start);
	expand->new[new_len - 1] = '\0';
	if (expand->word[expand->i] == '$' && sep == '"')
	{
		dollar_expand(expand, shell);
		quotes_expand(expand, sep, shell);
	}
	expand->quotes = 0;
	expand->i++;
}

void	expanded_one(t_expand *expand, t_shell *shell)
{
	expand->i = 0;
	expand->new = ft_calloc(1, 1);
	if (expand->new == NULL)
		return (free_all(shell), exit(25));
	while (expand->word[expand->i])
	{
		if (expand->word[expand->i] == '\'' && expand->quotes == 0)
			expand->quotes = 1;
		else if (expand->word[expand->i] == '"' && expand->quotes == 0)
			expand->quotes = 2;
		else if (expand->word[expand->i] == '\'' && expand->quotes == 1)
			expand->quotes = 0;
		else if (expand->word[expand->i] == '"' && expand->quotes == 2)
			expand->quotes = 0;
		if (expand->word[expand->i] == '$' && expand->quotes != 1)
			dollar_expand(expand, shell);
		else
			base_expand(expand, shell);
	}
}
void	expanded_two(t_expand *expand, t_shell *shell)
{
	expand->i = 0;
	expand->quotes = 0;
	expand->new = ft_calloc(1, 1);
	if (expand->new == NULL)
		return (free_all(shell), exit(25));
	while (expand->word[expand->i])
	{
		if (expand->word[expand->i] == '\'' && expand->quotes == 0)
			expand->quotes = 1;
		else if (expand->word[expand->i] == '"' && expand->quotes == 0)
			expand->quotes = 2;
		else if (expand->word[expand->i] == '\'' && expand->quotes == 1)
			expand->quotes = 0;
		else if (expand->word[expand->i] == '"' && expand->quotes == 2)
			expand->quotes = 0;
		if (expand->word[expand->i] == '\'' && expand->quotes == 1)
			quotes_expand(expand, '\'', shell);
		else if (expand->word[expand->i] == '"' && expand->quotes == 2)
			quotes_expand(expand, '"', shell);
		else
			base_expand(expand, shell);
	}
}
