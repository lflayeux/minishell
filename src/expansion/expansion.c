/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:07:12 by lflayeux          #+#    #+#             */
/*   Updated: 2025/07/27 15:42:08 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strjoin_free(char const *s1, char const *s2, t_shell *shell)
{
	char	*dest;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		dest = ft_strdup(s2);
		if (!dest)
			free_error(shell);
		return (dest);
	}
	i = 0;
	j = 0;
	dest = ft_calloc((ft_strlen(s1) + ft_strlen(s2)) + 1, sizeof(char));
	if (!dest)
		return (free((void *)s1), free_error(shell), NULL);
	while (s1[i])
		dest[i++] = s1[j++];
	j = 0;
	while (s2[j])
		dest[i++] = s2[j++];
	if (s1)
		free((void *)s1);
	return (dest);
}

int	new_prompt(t_shell *shell)
{
	t_tok	*tmp;
	char	*new_prompt;

	tmp = shell->tok;
	new_prompt = NULL;
	while (tmp)
	{
		if (new_prompt != NULL)
			new_prompt = ft_strjoin_free(new_prompt, " ", shell);
		if (tmp->type == WORD)
			new_prompt = ft_strjoin_free(new_prompt, tmp->word, shell);
		else
			new_prompt = ft_strjoin_free(new_prompt, get_token_name(tmp->type),
					shell);
		tmp = tmp->next;
	}
	ft_lstclear_tok(shell->tok);
	shell->tok = NULL;
	shell->input = new_prompt;
	return (TRUE);
}

int	expand_word(t_shell *shell, t_tok *tmp, t_expand *expand)
{
	if (tmp->type == WORD)
	{
		expand->word = tmp->word;
		expanded_one(expand, shell);
		if (ft_strcmp("", expand->new) == 0 && expand->new)
		{
			free(expand->new);
			expand->new = ft_strdup("\" \"");
			if (!expand->new)
				return (free_error(shell), FALSE);
		}
		if (expand->new)
		{
			free(expand->word);
			expand->word = expand->new;
			expand->new = NULL;
		}
		tmp->word = expand->word;
	}
	if (shell->var)
	{
		free(shell->var);
		shell->var = NULL;
	}
	return (TRUE);
}

void	unquotes(t_shell *shell, t_tok *tmp, t_expand *expand)
{
	if (tmp->type == WORD)
	{
		expand->word = tmp->word;
		expanded_two(expand, shell);
		if (expand->new)
		{
			free(expand->word);
			expand->word = expand->new;
		}
		tmp->word = expand->word;
	}
	if (shell->var)
	{
		free(shell->var);
		shell->var = NULL;
	}
}

int	expand(t_shell *shell)
{
	t_tok		*tmp;
	t_expand	*expand;

	tmp = shell->tok;
	expand = malloc(sizeof(t_expand));
	if (!expand)
		return (free_all(shell), exit(25), FALSE);
	expand->new = NULL;
	expand->quotes = 0;
	while (tmp)
	{
		expand_word(shell, tmp, expand);
		tmp = tmp->next;
	}
	new_prompt(shell);
	if (tokenize(shell) == FALSE)
		return (free(expand), FALSE);
	tmp = shell->tok;
	while (tmp)
	{
		unquotes(shell, tmp, expand);
		tmp = tmp->next;
	}
	free(expand);
	return (TRUE);
}
