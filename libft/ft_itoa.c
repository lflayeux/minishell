/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:36:58 by lflayeux          #+#    #+#             */
/*   Updated: 2024/11/26 19:49:23 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_intlen(long int n)
{
	int	count;

	count = 0;
	if (n <= 0)
	{
		count++;
		n *= -1;
	}
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*ft_printitoa(char *dest, long int n, int len)
{
	int	i;
	int	neg;

	neg = 0;
	i = len - 1;
	if (n < 0)
	{
		dest[neg] = '-';
		n *= -1;
	}
	while (n > 9)
	{
		dest[i] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	dest[i] = n + '0';
	dest[len] = '\0';
	return (dest);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		len;
	int		nb;

	nb = (int long)n;
	len = ft_intlen(nb);
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (0);
	ft_printitoa(dest, nb, len);
	return (dest);
}
