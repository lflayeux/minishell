/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:07:12 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/30 11:21:13 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	expand_word(t_expand *expand, t_shell *shell)
// {
// 	expanded_one(expand, shell);
// 	if (expand->new)
// 	{
// 		free(expand->word);
// 		expand->word = expand->new;
// 		expand->new = NULL;
// 	}
// 	expanded_two(expand, shell);
// 	if (expand->new)
// 	{
// 		free(expand->word);
// 		expand->word = expand->new;
// 	}
// }

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s1)
		return (ft_strdup(s2));
	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	dest = ft_calloc(len + 1, sizeof(char));
	if (!dest)
		return (0);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	if (s1)
		free((void *)s1);
	return (dest);
}
void	new_prompt(t_shell *shell)
{
	t_tok	*tmp;
	char	*new_prompt;

	tmp = shell->tok;
	new_prompt = NULL;
	while (tmp)
	{
		if (new_prompt != NULL)
			new_prompt = ft_strjoin_free(new_prompt, " ");
		if (tmp->type == WORD)
			new_prompt = ft_strjoin_free(new_prompt, tmp->word);
		else
			new_prompt = ft_strjoin_free(new_prompt, get_token_name(tmp->type));
		tmp = tmp->next;
	}
	ft_lstclear_tok(shell->tok);
	shell->tok = NULL;
	shell->input = new_prompt;
}

int	expand(t_shell *shell)
{
	t_tok		*tmp;
	t_expand	*expand;

	tmp = shell->tok;
	expand = malloc(sizeof(t_expand));
	expand->new = NULL;
	expand->quotes = 0;
	if (!expand)
		print_error("malloc", NULL, shell, GEN_ERROR);
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			expand->word = tmp->word;
			expanded_one(expand, shell);
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
		tmp = tmp->next;
	}
	new_prompt(shell);
	printf("%s\n", shell->input);
	if (tokenize(shell) == FALSE)
		return (FALSE);
	tmp = shell->tok;
	while (tmp)
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
		tmp = tmp->next;
	}
	free(expand);
	return (TRUE);
}
