/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:08:45 by lflayeux          #+#    #+#             */
/*   Updated: 2024/11/21 11:51:36 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;
	size_t	len_s;

	len_s = (size_t)ft_strlen((char *)s);
	i = 0;
	if (start >= len_s)
		len = 0;
	if (len > (len_s - start))
		len = (len_s - start);
	dest = (char *)ft_calloc((len + 1), sizeof(char));
	if (!dest)
		return (0);
	while ((start + i < len_s) && i < len)
	{
		dest[i] = s[start + i];
		i++;
	}
	return (dest);
}
