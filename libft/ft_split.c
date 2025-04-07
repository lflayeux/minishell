/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:28:20 by lflayeux          #+#    #+#             */
/*   Updated: 2024/11/26 19:49:41 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s[i] != c && s[i] != '\0')
		count++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static size_t	ft_next(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**ft_free(char **dest, int i)
{
	if (i > 0)
	{
		i = i - 1;
		while (i >= 0)
			free(dest[i--]);
	}
	free(dest);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		i;
	int		countwords;

	i = 0;
	countwords = ft_countwords(s, c);
	if (s == NULL)
		return (0);
	dest = (char **)ft_calloc(countwords + 1, sizeof(char *));
	if (dest == NULL)
		return (0);
	while (s)
	{
		while (*s && *s == c)
			s++;
		if (*s == '\0')
			break ;
		dest[i] = (char *)ft_calloc(ft_next(s, c) + 1, sizeof(char));
		if (dest[i] == NULL)
			return (ft_free(dest, i));
		ft_strlcpy(dest[i], s, ft_next(s, c) + 1);
		s += ft_next(s, c);
		i++;
	}
	return (dest);
}
