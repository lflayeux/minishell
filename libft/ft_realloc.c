/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherlaud <aherlaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 22:45:22 by pandemonium       #+#    #+#             */
/*   Updated: 2025/07/13 18:02:49 by aherlaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_realloc(char *ptr, size_t size)
{
	void	*new;
	size_t	len;

	if (ptr == NULL)
		return (ft_calloc(size, 1));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new = ft_calloc(size, 1);
	if (new == NULL)
		return (NULL);
	len = ft_strlen(ptr);
	if (len < size)
		ft_memcpy(new, ptr, len);
	else
		ft_memcpy(new, ptr, size);
	free(ptr);
	return (new);
}
