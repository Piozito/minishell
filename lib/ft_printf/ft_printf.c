/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaleixo- <aaleixo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:27:28 by aaleixo-          #+#    #+#             */
/*   Updated: 2025/03/09 14:34:33 by aaleixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	ft_putchar(char c, int *counter)
{
	write(1, &c, 1);
	(*counter)++;
	return (c);
}

void	ft_putstr(char *str, int *counter)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
		ft_putchar(str[i], counter);
}

void	ft_args(va_list args, char c, int *counter)
{
	char	*str;

	if (c == 'c')
		ft_putchar(va_arg(args, int), counter);
	else if (c == 's')
	{
		str = va_arg(args, char *);
		if (!str)
			str = "(null)";
		ft_putstr(str, counter);
	}
	else if (c == 'p')
		ft_ptr(args, counter);
	else if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(args, int), "0123456789", counter);
	else if (c == 'u')
		ft_putnbr(va_arg(args, unsigned int), "0123456789", counter);
	else if (c == 'x')
		ft_putnbr(va_arg(args, unsigned int), "0123456789abcdef", counter);
	else if (c == 'X')
		ft_putnbr(va_arg(args, unsigned int), "0123456789ABCDEF", counter);
	else if (c == '%')
		ft_putchar('%', counter);
}

int	ft_printf(const char *s, ...)
{
	unsigned int	i;
	int				counter;
	va_list			args;

	counter = 0;
	va_start(args, s);
	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			ft_args(args, s[i + 1], &counter);
			i += 2;
		}
		else
		{
			ft_putchar(s[i], &counter);
			i++;
		}
	}
	va_end(args);
	return (counter);
}

/* #include <limits.h>
#include <stdio.h>

int	main(void)
{
	ft_printf("aaaaaaaaaaaa %s faapsfasd: %i\n", "boas pessoal",
		ft_printf("faapsfasd"));
	printf("aaaaaaaaaaaa %s faapsfasd: %i\n", "boas pessoal",
	printf("faapsfasd"));
	ft_printf("Teste 1: %c\n", 'h');
	printf("Teste 1: %c\n", 'h');
	ft_printf("Teste 2: %s\n", "Boas pessoal");
	printf("Teste 2: %s\n", "Boas pessoal");
	ft_printf("Teste 3: %p\n", "eognaoowon");
	printf("Teste 3: %p\n", "eognaoowon");
	ft_printf("Teste 4: %d\n", -423778);
	printf("Teste 4: %d\n", -423778);
	ft_printf("Teste 5: %i\n", -423778);
	printf("Teste 5: %i\n", -423778);
	ft_printf("Teste 6: %u\n", -423778);
	printf("Teste 6: %u\n", -423778);
	ft_printf("Teste 7: %x\n", -423778);
	printf("Teste 7: %x\n", -423778);
	ft_printf("Teste 8: %X\n", -423778);
	printf("Teste 8: %X\n", -423778);
	ft_printf("Teste 9: %%\n");
	printf("Teste 9: %%\n");
	ft_printf("Teste 10: %c %s %p %d %i %u %x %X %%\n", 'h', "Boas pessoal",
		"eognaoowon", 423778, 423778, 423778, 423778, 423778);
	printf("Teste 10: %c %s %p %d %i %u %x %X %%\n", 'h', "Boas pessoal",
		"eognaoowon", 423778, 423778, 423778, 423778, 423778);
} */

/* int	main(int argc, char **argv)
{
	char *str;
	str = NULL;

	// ft_printf("Teste %d\n", ft_atoi(argv[1]));
	ft_printf("%p\n", str);
	(void)argv;
	(void)argc;
}*/
