/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrhexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:00:35 by lflayeux          #+#    #+#             */
/*   Updated: 2025/03/19 13:10:45 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbrhexa(unsigned long int nb)
{
	char				*hexa;
	int					count;

	hexa = "0123456789abcdef";
	count = 0;
	if (nb > 15)
		count += ft_putnbrhexa((nb / 16));
	count += ft_putchar(hexa[nb % 16]);
	return (count);
}
