/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 11:28:28 by pandemonium       #+#    #+#             */
/*   Updated: 2025/06/02 11:32:42 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isdelim(char c, char *delim)
{
	int	i;

	i = 0;
	while (delim[i])
	{
		if (delim[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*find_var_spe(char *s, int index, t_shell **shell)
{
	int		i;
	char	*var;
	int		len;

	len = 0;
	while (s[index + len] && ft_isdelim(s[index + len], "|<> \'\"") != 1)
		len++;
	var = ft_calloc((len + 1), sizeof(char));
	add_or_free(*shell, var, NULL, 0);
	i = 0;
	while (s[index] && ft_isdelim(s[index], "|<> \'\"") != 1)
		var[i++] = s[index++];
	return (var);
}
// PERMET DE RECALCULER LA BONNE LONGUEURE EN CAS DE $
int	dollar_len(char **token, int *i, t_shell **shell)
{
	int		len;
	char	*env_path;

	len = 0;
	(void)shell;
	(*i)++;
	if ((*token)[*i] == '$')
	{
		(*i)++;
		return (ft_strlen(get_pid(shell)));
	}
	//	else if (token[*i] == '$' &&  token[i + 1] == '?')
	else
	{
		if ((*token)[*i] == '\0' || (*token)[*i] == '"')
			return (1);
		env_path = getenv(find_var_spe(*token, *i, shell));
		if (env_path)
			len += ft_strlen(env_path);
	}
	return (len);
}

// PERMET DE RECALCULER LA BONNE LONGUEURE EN CAS DE '' OU ""
int	quotes_len(char **token, int *i, t_shell **shell)
{
	int	len;

	len = 0;
	if ((*token)[*i] == '\'')
	{
		(*i)++;
		while ((*token)[*i] != '\'' && (*token)[*i] != '\0')
		{
			(*i)++;
			len++;
		}
		(*i)++;
	}
	else if ((*token)[*i] == '"')
	{
		(*i)++;
		while ((*token)[*i] != '"' && (*token)[*i] != '\0')
		{
			if ((*token)[*i] == '$')
				len += dollar_len(token, i, shell);
			else
			{
				// printf("%d i\n", *i);
				(*i)++;
				len++;
			}
		}
		(*i)++;
	}
	return (len);
}

// FONCTION GLOBALE POUR LE RECALCUL DES ' " et $
int	expansion_len(char **token, t_shell **shell)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while ((*token)[i])
	{
		while ((*token)[i] != '\0' && (*token)[i] != '\'' && (*token)[i] != '"'
			&& (*token)[i] != '$')
		{
			i++;
			len++;
		}
		// printf("%d iexp\n", i);
		if ((*token)[i] != '\'' || (*token)[i] != '"')
			len += quotes_len(token, &i, shell);
		if ((*token)[i] == '$')
			len += dollar_len(token, &i, shell);
	}
	return (len);
}