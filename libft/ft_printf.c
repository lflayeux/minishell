/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflayeux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:00:00 by lflayeux          #+#    #+#             */
/*   Updated: 2025/03/19 13:11:44 by lflayeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_rules_print(const char *format, va_list args)
{
	void	*ptr;

	if (*format == 'c')
		return (ft_putchar((char)va_arg(args, int)));
	else if (*format == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (*format == 'p')
	{
		ptr = va_arg(args, void *);
		if (!ptr)
			return (ft_putstr("(nil)"));
		return (ft_putstr("0x") + ft_putnbrhexa((unsigned int long)ptr));
	}
	else if (*format == 'd' || *format == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (*format == 'u')
		return (ft_putnbr(va_arg(args, unsigned int)));
	else if (*format == 'x')
		return (ft_putnbrhexa((unsigned long)va_arg(args, unsigned int)));
	else if (*format == 'X')
		return (ft_putnbrhexa_up((unsigned long)va_arg(args, unsigned int)));
	else if (*format == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	if (!format)
		return (-1);
	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
			count += ft_rules_print(++format, args);
		else
			count += ft_putchar(*format);
		++format;
	}
	va_end(args);
	return (count);
}
/*
int main()
{	
	char *str;
	char **ptr = &str;


	str = "best";

	printf("\n MY RESULT \n");

	printf("%i\n", ft_printf("salut mec %s\n", "ca va"));
	printf("%i\n", ft_printf(NULL));
	printf("%i\n", ft_printf("d%c\n", 'e'));
	printf("%i\n", ft_printf("20%%\n"));
	printf("%i\n", ft_printf("adresse de str --> %p\n", ptr));
	printf("%i\n", ft_printf("%d\n", -2569845));
	printf("%i\n", ft_printf("%i\n", -2569845));
	printf("%i\n", ft_printf("%u\n", -2569845));
	printf("%i\n", ft_printf("%x\n", -2569845));
	printf("%i\n", ft_printf("%X\n", -2569845));

	printf("\n TRUE RESULT \n");

	printf("%i\n", printf("salut mec %s\n", "ca va"));
	printf("%i\n", printf(NULL));
	printf("%i\n", printf("d%c\n", 'e'));
	printf("%i\n", printf("20%%\n"));
	printf("%i\n", printf("adresse de str --> %p\n", ptr));
	printf("%i\n", printf("%d\n", -2569845));
	printf("%i\n", printf("%i\n", -2569845));
	printf("%i\n", printf("%u\n", -2569845));
	printf("%i\n", printf("%x\n", -2569845));
	printf("%i\n", printf("%X\n", -2569845));
}*/
