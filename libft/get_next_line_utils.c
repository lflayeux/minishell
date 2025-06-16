/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pandemonium <pandemonium@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:58:39 by lflayeux          #+#    #+#             */
/*   Updated: 2025/06/14 00:42:02 by pandemonium      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_calloc_gnl(size_t nb, size_t size)
{
	size_t		i;
	char		*str;

	i = 0;
	str = malloc(nb * size);
	if (str == NULL)
		return (NULL);
	while (i < nb)
	{
		*(str + i) = '\0';
		i++;
	}
	return (str);
}

int	ft_strchr_split(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	dest = ft_calloc_gnl(len + 1, sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dest[i + j] = s2[j];
		j++;
	}
	return (dest);
}

char	*ft_realloc_gnl(char *buf, char *full_buf)
{
	char	*new;

	new = ft_strjoin_gnl(buf, full_buf);
	if (new == NULL)
		return (NULL);
	free(buf);
	return (new);
}
