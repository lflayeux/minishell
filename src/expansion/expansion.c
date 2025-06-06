/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:07:12 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/07 01:01:07 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_dollar_valid(char *word)
{
	int i;
	int quotes;

	i = 0;
	quotes = 0;
	while (word[i])
	{
		if (word[i] == '$' && !quotes)
			return (1);
		else if (word[i] == '\'' && !quotes)
			quotes = 1;
		else if (word[i] == '\'' && quotes == 1)
			quotes = 0;
		i++;
	}
	return (0);
}
void	find_var_spe(char **word, t_shell *shell)
{
	int		len;
	int		i;
	int		j;

	len = 0;
	i = 0;
	j = 0;
	while ((*word)[len] && !is_space((*word)[len]) && !is_symbol((*word)[len]))
		len++;
	shell->var = ft_calloc((len + 1), sizeof(char));
	if (!shell->var)
        print_error(shell, MALLOC);
	i = 0;
	while ((*word)[i] && !is_space((*word)[i]) && !is_symbol((*word)[i]))
		shell->var[j++] = (*word)[i++];
}

int	len_dollar(char *word, t_shell *shell)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (word[i])
	{
		if (word[i] == '$' && word[i + 1] && word[i + 1] == '$')
		{
			i += 2;
			len += ft_strlen(shell->pid);
		}
		else if (word[i] == '$' && word[i + 1] && word[i + 1] == '?')
		{
			i += 2;
			len += ft_intlen(shell->error);
		}
		else if (word[i] == '$' && word[i + 1])
		{
			i += ft_strlen(find_var_spe(&word[i], shell));
			len += ft_strlen(ft_get_env(find_var(&word[i], shell)));
		}
	}
	return (len);
}

void	expand_dollar(t_tok *tok, t_shell shell)
{
	// calcul taille apres  dollar 
	// realloc word avec word changer
	int	len;

	len = 0;
	len += len_dollar(tok->word, shell);
}

int	check_dollar(t_tok *token)
{
	int	i;
	t_tok	*tmp;

	i = 0;
	while (tmp)
	{
		if (tmp->word && is_dollar_valid(tmp->word))
			expand_dollar(tmp, shell);
		tmp = tmp->next;
	}
	return (0);
}

void	expand(t_shell *shell)
{
    check_dollar(shell);
}