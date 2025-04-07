/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrhexa_up.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:10:55 by lflayeux          #+#    #+#             */
/*   Updated: 2025/03/19 13:10:36 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbrhexa_up(unsigned long int nb)
{
	char				*hexa;
	int					count;

	hexa = "0123456789ABCDEF";
	count = 0;
	if (nb > 15)
		count += ft_putnbrhexa_up((nb / 16));
	count += ft_putchar(hexa[nb % 16]);
	return (count);
}
