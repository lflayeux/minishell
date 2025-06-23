/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:07:12 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/23 14:39:14 by aherlaud         ###   ########.fr       */
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

void	new_prompt(t_shell *shell)
{
	t_tok	*tmp;
	char	*new_prompt;

	// char	*new_tmp;
	tmp = shell->tok;
	new_prompt = "";
	while (tmp)
	{
		if (ft_strcmp(new_prompt, "") != 0)
			new_prompt = ft_strjoin(new_prompt, " ");
		if (tmp->type == WORD)
			new_prompt = ft_strjoin(new_prompt, tmp->word);
		else
			new_prompt = ft_strjoin(new_prompt, get_token_name(tmp->type));
		// if (new_tmp)
		// 	free(new_tmp);
		tmp = tmp->next;
	}
	ft_lstclear_tok(shell->tok);
	shell->tok = NULL;
	shell->input = new_prompt;
}

void	expand(t_shell *shell)
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
	tokenize(shell);
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
}
