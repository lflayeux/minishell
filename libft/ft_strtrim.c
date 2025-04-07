/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:56:56 by lflayeux          #+#    #+#             */
/*   Updated: 2024/11/20 19:54:55 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_set(char s1, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	int		i;
	int		start;
	int		end;

	i = 0;
	start = 0;
	end = ft_strlen((char *)s1);
	while (start < end && check_set(s1[start], set))
		start++;
	while (start < end && check_set(s1[end - 1], set))
		end--;
	dest = malloc((end - start + 1) * sizeof(char));
	if (!dest)
		return (0);
	while (start < end)
		dest[i++] = s1[start++];
	dest[i] = '\0';
	return (dest);
}
