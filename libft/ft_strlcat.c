/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:43:36 by lflayeux          #+#    #+#             */
/*   Updated: 2025/09/23 20:01:01 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	i = 0;
	len_dst = ft_strlen((const char *)dst);
	len_src = ft_strlen(src);
	if (n - 1 >= len_dst && n > 0)
	{
		while (n - 1 > len_dst + i && src[i])
		{
			dst[len_dst + i] = src[i];
			i++;
		}
		dst[len_dst + i] = '\0';
	}
	if (n <= len_dst)
		len_dst = n;
	return (len_dst + len_src);
}
