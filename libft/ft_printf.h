/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:14:09 by lflayeux          #+#    #+#             */
/*   Updated: 2024/12/02 18:19:46 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_putnbrhexa(unsigned long int nb);

int	ft_putnbrhexa_up(unsigned long int nb);

int	ft_putchar(int c);

int	ft_putstr(char *str);

int	ft_putnbr(long int nb);

int	ft_printf(const char *format, ...);

#endif
