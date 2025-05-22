/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:35:57 by alex              #+#    #+#             */
/*   Updated: 2025/05/22 16:02:57 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_countword(const char *str, char c)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			index++;
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
			index++;
		}
		i++;
	}
	return (index);
}

static int	ft_wordlen(const char *s, int start, char c)
{
	int	len;

	len = 0;
	if (s[start] == '\'')
	{
		start++;
		while (s[start + len] && s[start + len] != '\'')
			len++;
		return (len);
	}
	while (s[start + len] && s[start + len] != c)
		len++;
	return (len);
}

static char	*ft_strcpy_dif(char *dst, const char *src, int len, int start)
{
	int	i;

	i = 0;
	if (src[start] == '\'')
		start++;
	while (i < len)
	{
		dst[i++] = src[start++];
	}
	dst[i] = '\0';
	return (dst);
}

char	**ft_split_dif(char const *s, char c)
{
	char	**tab;
	int		i;
	int		num;

	i = 0;
	num = 0;
	tab = malloc((ft_countword(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0' && ft_countword(s, c) > 0)
		{
			tab[num] = malloc((ft_wordlen(s, i, c) + 1) * sizeof(char));
			ft_strcpy_dif(tab[num], s, ft_wordlen(s, i, c), i);
			num++;
		}
		if (s[i] == '\'')
			i += ft_wordlen(s, i, c) + 2;
		else
			i += ft_wordlen(s, i, c);
	}
	return (tab[num] = NULL, tab);
}
