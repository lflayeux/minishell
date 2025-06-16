	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:07:12 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/14 13:24:55 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	quotes_expand(t_expand *expand, char sep, t_shell *shell);

void	ft_getenv(char **env, char *word, t_expand *expand, t_shell *shell)
{
	int		i = 0;
	int		len = 0;

	if (!env || !shell)
		return ;
	while (ft_isalnum(word[len]) || word[len] == '_')
	{
		len++;
		expand->i++;
	}
	while (env[i])
	{
		if (!ft_strncmp(env[i], word, len) && env[i][len] == '=')
		{
			shell->var = ft_strdup(&env[i][len + 1]);
			if (!shell->var)
				print_error(shell, MALLOC);
		}
		i++;
	}
}


void	pid_expand(t_expand *expand, t_shell *shell)
{
	expand->i++;
	expand->new = ft_realloc(expand->new, strlen(expand->new) + strlen(shell->pid) + 1);
	if (!expand->new)
		print_error(shell, MALLOC);
	ft_strlcat(expand->new, shell->pid, strlen(expand->new) + strlen(shell->pid) + 1);
}

void	error_expand(t_expand *expand, t_shell *shell)
{
	char	*error_str;

	expand->i++;
	error_str = ft_itoa((int)shell->error);
	if (!error_str)
		print_error(shell, MALLOC);
	expand->new = ft_realloc(expand->new, strlen(expand->new) + strlen(error_str) + 1);
	if (!expand->new)
		print_error(shell, MALLOC);
	ft_strlcat(expand->new, error_str, strlen(expand->new) + strlen(error_str) + 1);
	free(error_str);
}
void	base_expand(t_expand *expand, t_shell *shell)
{
	expand->new = ft_realloc(expand->new, strlen(expand->new) + 2);
	if (!expand->new)
		print_error(shell, MALLOC);
	expand->new[ft_strlen(expand->new)] = expand->word[expand->i];
	expand->i++;
}
void	var_expand(t_expand *expand, t_shell *shell)
{

	ft_getenv(shell->env, &(expand->word[expand->i]), expand, shell);
	if (shell->var == NULL)
	{
		base_expand(expand, shell);
		return ;
	}
	expand->new = ft_realloc(expand->new, strlen(expand->new) + strlen(shell->var) + 1);
	if (!expand->new)
		print_error(shell, MALLOC);
	ft_strlcat(expand->new, shell->var, strlen(expand->new) + strlen(shell->var) + 1);
}


void	dollar_expand(t_expand *expand, t_shell *shell)
{
	expand->i++;
	if ((expand->word[expand->i] == '"' || expand->word[expand->i] == '"') && expand->quotes)
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
	else if (ft_isalnum(expand->word[expand->i]) || \
			expand->word[expand->i] == '_')
		var_expand(expand, shell);
	else
	{
		expand->i--;
		base_expand(expand, shell);
	}
}


void	quotes_expand(t_expand *expand, char sep, t_shell *shell)
{	
	int		start;

	start = expand->i;
	while (expand->word[expand->i] != sep && expand->word[expand->i])
	{
		if (expand->word[expand->i] == '$' && sep == '"')
			break;
		expand->i++;
	}
	expand->new = ft_realloc(expand->new, strlen(expand->new) \
			+ (expand->i - start) + 1);
	if (expand->new == NULL)
		print_error(shell, MALLOC);
	ft_strlcat(expand->new, &(expand->word[start]), expand->i - start + 1);
	if (expand->word[expand->i] == '$' && sep == '"')
	{
		dollar_expand(expand, shell);
		quotes_expand(expand, sep, shell);
	}
	expand->i++;
}

void	expanded_one(t_expand *expand, t_shell *shell)
{
	expand->i = 0;
	expand->new = ft_calloc(1, 1);
	if (expand->new == NULL)
		print_error(shell, MALLOC);
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
	expand->new = ft_calloc(1, 1);
	if (expand->new == NULL)
		print_error(shell, MALLOC);
	while (expand->word[expand->i])
	{
		if (expand->word[expand->i] == '\'')
			quotes_expand(expand, '\'', shell);
		else if (expand->word[expand->i] == '"')
			quotes_expand(expand, '"', shell);
		else
			base_expand(expand, shell);
	}

}
void	expand_word(t_expand *expand, t_shell *shell)
{
	expanded_one(expand, shell);
	if (expand->new)
	{
		free(expand->word);
		expand->word = expand->new;
	}

	printf("%s\n", expand->word);
	expanded_two(expand, shell);
	if (expand->new)
	{
		free(expand->word);
		expand->word = expand->new;
	}
	printf("%s\n", expand->word);
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
		print_error(shell, MALLOC);
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			expand->word = tmp->word;
			expand_word(expand, shell);
		}
		if (shell->var)
		{
			free(shell->var);
			shell->var = NULL;
		}
		tmp = tmp->next;
	}
}
