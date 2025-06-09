/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <lflayeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:07:12 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/09 17:50:05 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	find_var_spe(char *word, t_shell *shell)
{
	int		len;
	int		i;
	int		j;

	len = 0;
	i = 0;
	j = 0;
	while (word[len] && (ft_isalnum(word[len]) || word[len] == '_'))
		len++;
	shell->var = ft_calloc((len + 1), sizeof(char));
	if (!shell->var)
        print_error(shell, MALLOC);
	i = 0;
	while (word[i] && (ft_isalnum(word[i]) || word[i] == '_'))
		shell->var[j++] = word[i++];
}
char	*ft_getenv(char **env, t_shell *shell)
{
	int	i;
	int	len;

	i = 0;
	if (!env || !shell || !shell->var)
		return (NULL);

	len = ft_strlen(shell->var);
	while (env[i])
	{
		if (!ft_strncmp(env[i], shell->var, len) && env[i][len] == '=')
			return (&env[i][len + 1]);
		i++;
	}
	return (NULL);
}
// PERMET DE RECALCULER LA BONNE LONGUEURE EN CAS DE $
int	dollar_len(char *word, int *i, t_shell *shell)
{
	int		len;
	char	*env_path;

	len = 0;
	(void)shell;
	(*i)++;
	if (word[*i] == '$')
	{
		(*i)++;
		return (ft_strlen(shell->pid));
	}
	else if (word[*i] == '$' &&  word[i + 1] == '?')
	{
		(*i)++;
		return (ft_strlen(shell->pid));		
	}
	else
	{
		if (word[*i] == '\0' || word[*i] == '"')
			return (1);
		env_path = getenv(find_var_spe(word, *i, shell));
		if (env_path)
			len += ft_strlen(env_path);
	}
	return (len);
}

int	quotes_len(char *word, int *i, t_shell *shell)
{
	int	len;

	len = 0;
	if (word[*i] == '\'')
	{
		(*i)++;
		while (word[*i] != '\'' && word[*i] != '\0')
		{
			(*i)++;
			len++;
		}
		(*i)++;
	}
	else if (word[*i] == '"')
	{
		(*i)++;
		while (word[*i] != '"' && word[*i] != '\0')
		{
			if (word[*i] == '$')
				len += dollar_len(word, i, shell);
			else
			{
				(*i)++;
				len++;
			}
		}
		(*i)++;
	}
	return (len);
}

// FONCTION GLOBALE POUR LE RECALCUL DES ' " et $
int	expansion_len(char *word, t_shell *shell)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (word[i])
	{
		while (word[i] != '\0' && word[i] != '\'' && word[i] != '"'
			&& word[i] != '$')
		{
			i++;
			len++;
		}
		if (word[i] != '\'' || word[i] != '"')
			len += quotes_len(word, &i, shell);
		if (word[i] == '$')
			len += dollar_len(word, &i, shell);
	}
	return (len);
}

void	expand(t_shell *shell)
{
	int	i;
	t_tok	*tmp;

	i = 0;
	tmp = shell->tok;
	while (tmp)
	{
		expansion_len(tmp->word, shell);
		tmp = tmp->next;
	}
}