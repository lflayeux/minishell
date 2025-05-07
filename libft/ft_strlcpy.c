/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:14:53 by lflayeux          #+#    #+#             */
/*   Updated: 2024/11/20 18:53:51 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (src[i] && (i + 1 < len))
	{
		dst[i] = src[i];
		i++;
	}
	if (len > 0)
	{
		dst[i] = '\0';
		i++;
	}
	return (ft_strlen((char *)src));
}
